#ifndef _HGPARALLEL_H_
#define _HGPARALLEL_H_

#ifdef BL_USE_NEW_HFILES
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <MultiFab.H>

#ifdef BL_USE_MPI
#include <mpi.h>
#else
#error Must define BL_USE_MPI in this file
#endif

inline int processor_number()
{
    return ParallelDescriptor::MyProc();
}

inline int processor_number(const MultiFab&r, int igrid)
{
    return r.DistributionMap()[igrid];
}

inline bool is_remote(const MultiFab& r, int igrid)
{
    return ParallelDescriptor::MyProc() != processor_number(r, igrid);
}

inline bool is_local(const MultiFab& r, int igrid)
{
    return ParallelDescriptor::MyProc() == processor_number(r, igrid);
}

#ifdef BL_USE_NEW_HFILES
#include <list>
using namespace std;
#else
#include <list.h>
#endif

class task
{
public:
    typedef unsigned int sequence_number;
    task() : m_sno(~0U), m_started(false) {}
    virtual ~task() {}
    virtual bool ready() = 0;
    virtual bool init(sequence_number sno, MPI_Comm comm)
    {
	m_sno  = sno;
	m_comm = comm;
	return false;
    }
    virtual void hint() const { };
    void set_sequence_number(sequence_number sno)
    {
	m_sno = sno;
    }
    sequence_number get_sequence_number() const
    {
	return m_sno;
    }
    virtual bool depends_on_q(const task* t1) const
    {
	return false;
    }
    void depend_on(task*& t1)
    {
	dependencies.push_back( &t1 );
    }
    bool depend_ready();
protected:
    sequence_number m_sno;
    list< task** > dependencies;
    bool m_started;
    MPI_Comm m_comm;
};

// The list...
class task_list
{
public:
    explicit task_list( MPI_Comm comm = MPI_COMM_WORLD );
    ~task_list();
    void add_task(task* t);
    void execute();
    bool execute_no_block();
	// executes once through the task list, return true if any elements left
    const MPI_Comm& mpi_comm() const { return comm; }
    bool empty() const { return tasks.empty(); }
private:
    list< task** > tasks;
    MPI_Comm comm;
    task::sequence_number seq_no;
    bool verbose;
    static bool def_verbose;
};

class task_copy : public task
{
public:
    task_copy(MultiFab& mf, int dgrid,                const MultiFab& smf, int sgrid, const Box& bx);
    task_copy(MultiFab& mf, int dgrid, const Box& db, const MultiFab& smf, int sgrid, const Box& sb);
    virtual ~task_copy();
    virtual bool ready();
    virtual bool init(sequence_number sno, MPI_Comm comm);
    virtual void hint() const;
    virtual bool depends_on_q(const task* t) const;
protected:
    void startup();
    MPI_Request m_request;
    FArrayBox* tmp;
    MultiFab& m_mf;
    const MultiFab& m_smf;
    int m_dgrid;
    const int m_sgrid;
    const Box m_bx;
    const Box m_sbx;
    bool m_local;
};

class task_fab : public task
{
public:
    task_fab(const MultiFab&t_, int tt_, const Box& region_, int ncomp_)
	: m_local_target(is_local(t_, tt_)), region(region_), ncomp(ncomp_), target(0) {}
    virtual ~task_fab()
    {
	delete target;
    }
    virtual const FArrayBox& fab();
    virtual bool init(sequence_number sno, MPI_Comm comm);
protected:
    const Box region;
    const int ncomp;
    FArrayBox* target;
    bool m_local_target;
};

class level_interface;
class amr_boundary_class;

class task_fill_patch : public task_fab
{
public:
    task_fill_patch(const MultiFab& t_, int tt_, const Box& region_, const MultiFab& r_, const level_interface& lev_interface_, const amr_boundary_class* bdy_, int idim_ = 0, int index_ = 0);
    virtual ~task_fill_patch();
    virtual bool ready();
    virtual bool init(sequence_number sno, MPI_Comm comm);
private:
    bool fill_patch_blindly();
    bool fill_exterior_patch_blindly();
    void fill_patch();
private:
    const MultiFab& r;
    const level_interface& lev_interface;
    const amr_boundary_class* bdy;
    const int idim;
    const int index;
    task_list tl;
};

class task_fab_get : public task_fab
{
public:
    task_fab_get(const MultiFab& d_, int dgrid_, const Box& bx, const MultiFab& s_, int sgrid_);
    virtual ~task_fab_get();
    virtual bool ready();
    virtual bool init(sequence_number sno, MPI_Comm comm);
private:
    const MultiFab& s;
    const int sgrid;
    const Box bx;
};

class task_fec_base : public task
{
public:
    task_fec_base(const list<int>& tll_, const Box& freg_, MultiFab& s_, int igrid_)
	: tll(tll_), freg(freg_), s(s_), igrid(igrid_)
    {
    }
    task_fec_base( MultiFab& s_, int igrid_)
	: s(s_), igrid(igrid_)
    {
    }
    virtual ~task_fec_base()
    {
	for( vector<task_fab*>::iterator tfi = tfvect.begin(); tfi != tfvect.end(); ++tfi)
	{
	    delete *tfi;
	}
    }
	
    virtual bool init(sequence_number sno, MPI_Comm comm)
    {
	task::init(sno, comm);
	bool result = is_local(s, igrid);
	for(int i = 0; i < BL_SPACEDIM; ++i)
	{
	    bool tresult = tfvect[i]->init(sno, comm);
	    result = tresult ||  result;
	}
	list<int>::const_iterator tli = tll.begin();
	while ( tli != tll.end() )
	{
	    bool tresult = is_local(s, *tli++);
	    result = result || tresult;
	}
        return result;
    }
    virtual bool ready()
    {
	bool result = true;
	for(vector<task_fab*>::iterator tfi = tfvect.begin(); tfi != tfvect.end(); ++tfi)
	{
	    bool tresult = (*tfi)->ready();
	    result = tresult && result;
	}
	if ( !result ) return false;
	return true;
    }
protected:
    void push_back(task_fab* tf)
    {
	tfvect.push_back(tf);
    }
    bool is_local_target() const
    {
	return is_local(s, igrid);
    }
    FArrayBox& target_fab()
    {
	assert ( is_local_target() );
	return s[igrid];
    }
    int grid_number() const
    {
	return igrid;
    }
    const FArrayBox& task_fab_result(int n)
    {
	if ( n < 0 || n >= tfvect.size() ) throw( "bad_arg" );
	return tfvect[n]->fab();
    }
private:
    const list<int> tll;
    const Box freg;
    MultiFab& s;
    int igrid;
    vector<task_fab*> tfvect;
};

#endif

