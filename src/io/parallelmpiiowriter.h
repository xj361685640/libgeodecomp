#include <libgeodecomp/config.h>
#ifdef LIBGEODECOMP_FEATURE_MPI
#ifndef LIBGEODECOMP_IO_PARALLELMPIIOWRITER_H
#define LIBGEODECOMP_IO_PARALLELMPIIOWRITER_H

#include <libgeodecomp/io/mpiio.h>
#include <libgeodecomp/io/parallelwriter.h>
#include <libgeodecomp/mpilayer/typemaps.h>

namespace LibGeoDecomp {

template<typename CELL_TYPE>
class ParallelMPIIOWriter : public ParallelWriter<CELL_TYPE>
{
public:
    friend class ParallelMPIIOWriterTest;
    typedef typename ParallelWriter<CELL_TYPE>::GridType GridType;
    typedef typename APITraits::SelectTopology<CELL_TYPE>::Value Topology;
    static const int DIM = Topology::DIM;

    ParallelMPIIOWriter(
        const std::string& prefix,
        const unsigned period,
        const unsigned maxSteps,
        const MPI::Intracomm& communicator = MPI::COMM_WORLD,
        MPI::Datatype mpiDatatype = Typemaps::lookup<CELL_TYPE>()) :
        ParallelWriter<CELL_TYPE>(prefix, period),
        maxSteps(maxSteps),
        comm(communicator),
        datatype(mpiDatatype)
    {}

    virtual void stepFinished(
        const GridType& grid,
        const Region<Topology::DIM>& validRegion,
        const Coord<Topology::DIM>& globalDimensions,
        unsigned step,
        WriterEvent event,
        std::size_t rank,
        bool lastCall)
    {
        if ((event == WRITER_STEP_FINISHED) && (step % period != 0)) {
            return;
        }

        MPIIO<CELL_TYPE>::writeRegion(
            grid,
            globalDimensions,
            step,
            maxSteps,
            filename(step),
            validRegion,
            datatype,
            comm);
    }

private:
    using ParallelWriter<CELL_TYPE>::period;
    using ParallelWriter<CELL_TYPE>::prefix;

    unsigned maxSteps;
    MPI::Intracomm comm;
    MPI::Datatype datatype;

    std::string filename(unsigned step) const
    {
        std::ostringstream buf;
        buf << prefix << std::setfill('0') << std::setw(5) << step << ".mpiio";
        return buf.str();
    }
};

}

#endif
#endif
