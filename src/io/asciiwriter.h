#include <libgeodecomp/config.h>
#ifdef LIBGEODECOMP_FEATURE_MPI
#ifndef _libgeodecomp_io_asciiwriter_h_
#define _libgeodecomp_io_asciiwriter_h_

#include <string>
#include <cerrno>
#include <fstream>
#include <iomanip>
#include <libgeodecomp/parallelization/simulator.h>
#include <libgeodecomp/io/image.h>
#include <libgeodecomp/io/ioexception.h>
#include <libgeodecomp/io/plotter.h>
#include <libgeodecomp/io/writer.h>

namespace LibGeoDecomp {

/**
 * An output plugin for writing text files. Uses the same selector
 * infrastucture as the BOVWriter.
 */
template<typename CELL_TYPE, typename ATTRIBUTE_SELECTOR>
class ASCIIWriter : public Writer<CELL_TYPE>
{    
    friend class ASCIIWriterTest;
public:
    static const int DIM = CELL_TYPE::Topology::DIMENSIONS;

    using Writer<CELL_TYPE>::sim;
    using Writer<CELL_TYPE>::period;
    using Writer<CELL_TYPE>::prefix;

    ASCIIWriter(
        const std::string& prefix, 
        MonolithicSimulator<CELL_TYPE> *sim, 
        const unsigned& period = 1) :
        Writer<CELL_TYPE>(prefix, sim, period)
    {}

    virtual void initialized()
    {
        writeStep();
    }

    virtual void stepFinished()
    {
        if (sim->getStep() % period == 0) {
            writeStep();
        }
    }

    virtual void allDone() 
    {
        writeStep();
    }

 private:
    void writeStep()
    {
        const Grid<CELL_TYPE> *grid = sim->getGrid();

        std::ostringstream filename;
        filename << prefix << "." << std::setfill('0') << std::setw(4)
                 << sim->getStep() << ".ascii";
        std::ofstream outfile(filename.str().c_str());
        if (!outfile) {
            throw FileOpenException("Cannot open output file", 
                                    filename.str(), errno);
        }

        CoordBox<DIM> box = grid->boundingBox();
        for (typename CoordBox<DIM>::Iterator i = box.begin(); i != box.end(); ++i) {
            if ((*i)[0] == 0) {
                for (int d = 0; d < DIM; ++d) {
                    if ((*i)[d] == 0) {
                        outfile << "\n";
                    }
                }
            }
            outfile << ATTRIBUTE_SELECTOR()((*grid)[*i]) << " ";
        }

        if (!outfile.good()) {
            throw FileWriteException("Cannot write to output file",
                                     filename.str(), errno);
        }
        outfile.close();
    }
};

}

#endif
#endif
