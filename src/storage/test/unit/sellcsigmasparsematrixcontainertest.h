#include <libgeodecomp/storage/sellcsigmasparsematrixcontainer.h>
#include <cxxtest/TestSuite.h>
#include <iostream>


using namespace LibGeoDecomp;

namespace LibGeoDecomp {

class SellCSigmaSparseMatrixContainerTest : public CxxTest::TestSuite
{
public:
    // test with a 8x8 diagonal Matrix, C = 1; Sigma = 1
    void testGetRow_one()
    {
//std::cout << "\n\n\nTEST 1: C=1 Sigma=1 Diagonalmatrix sotiert" <<std::endl;
        SellCSigmaSparseMatrixContainer<int, 1, 1> smc;

        /* add a test 8x8 Matrix:
         * 1 0 0 0 0 0 0 0
         * 0 2 0 0 0 0 0 0
         * 0 0 3 0 0 0 0 0
         * 0 0 0 4 0 0 0 0
         * 0 0 0 0 5 0 0 0
         * 0 0 0 0 0 6 0 0
         * 0 0 0 0 0 0 7 0
         * 0 0 0 0 0 0 0 8
         */

        smc.addPoint (0, 0, 1);
        smc.addPoint (1, 1, 2);
        smc.addPoint (2, 2, 3);
        smc.addPoint (3, 3, 4);
        smc.addPoint (4, 4, 5);
        smc.addPoint (5, 5, 6);
        smc.addPoint (6, 6, 7);
        smc.addPoint (7, 7, 8);

        std::vector< std::pair<int, int> > row0;
        std::pair<int, int> pair0 (0,1);
        row0.push_back(pair0);
        std::vector< std::pair<int, int> > row1;
        std::pair<int, int> pair1 (1,2);
        row1.push_back(pair1);
        std::vector< std::pair<int, int> > row2;
        std::pair<int, int> pair2 (2,3);
        row2.push_back(pair2);
        std::vector< std::pair<int, int> > row3;
        std::pair<int, int> pair3 (3,4);
        row3.push_back(pair3);
        std::vector< std::pair<int, int> > row4;
        std::pair<int, int> pair4 (4,5);
        row4.push_back(pair4);
        std::vector< std::pair<int, int> > row5;
        std::pair<int, int> pair5 (5,6);
        row5.push_back(pair5);
        std::vector< std::pair<int, int> > row6;
        std::pair<int, int> pair6 (6,7);
        row6.push_back(pair6);
        std::vector< std::pair<int, int> > row7;
        std::pair<int, int> pair7 (7,8);
        row7.push_back(pair7);

        TS_ASSERT_EQUALS(
                smc.getRow(0),
                row0
                );
        TS_ASSERT_EQUALS(
                smc.getRow(1),
                row1
                );
        TS_ASSERT_EQUALS(
                smc.getRow(2),
                row2
                );
        TS_ASSERT_EQUALS(
                smc.getRow(3),
                row3
                );
        TS_ASSERT_EQUALS(
                smc.getRow(4),
                row4
                );
        TS_ASSERT_EQUALS(
                smc.getRow(5),
                row5
                );
        TS_ASSERT_EQUALS(
                smc.getRow(6),
                row6
                );
        TS_ASSERT_EQUALS(
                smc.getRow(7),
                row7
                );
    }

    // test with a 8x8 diagonal Matrix, C = 1; Sigma = 1
    // randome addPoints
    void testGetRow_two()
    {
//std::cout << "\n\n\nTEST 2: C=1 Sigma=1 Diagonalmatrix" <<std::endl;
        SellCSigmaSparseMatrixContainer<int, 1, 1> smc;

        /* add a test 8x8 Matrix:
         * 1 0 0 0 0 0 0 0
         * 0 2 0 0 0 0 0 0
         * 0 0 3 0 0 0 0 0
         * 0 0 0 4 0 0 0 0
         * 0 0 0 0 5 0 0 0
         * 0 0 0 0 0 6 0 0
         * 0 0 0 0 0 0 7 0
         * 0 0 0 0 0 0 0 8
         */

        smc.addPoint (1, 1, 2);
        smc.addPoint (0, 0, 1);
        smc.addPoint (6, 6, 7);
        smc.addPoint (4, 4, 5);
        smc.addPoint (7, 7, 8);
        smc.addPoint (2, 2, 3);
        smc.addPoint (5, 5, 6);
        smc.addPoint (3, 3, 4);

        std::vector< std::pair<int, int> > row0;
        std::pair<int, int> pair0 (0,1);
        row0.push_back(pair0);
        std::vector< std::pair<int, int> > row1;
        std::pair<int, int> pair1 (1,2);
        row1.push_back(pair1);
        std::vector< std::pair<int, int> > row2;
        std::pair<int, int> pair2 (2,3);
        row2.push_back(pair2);
        std::vector< std::pair<int, int> > row3;
        std::pair<int, int> pair3 (3,4);
        row3.push_back(pair3);
        std::vector< std::pair<int, int> > row4;
        std::pair<int, int> pair4 (4,5);
        row4.push_back(pair4);
        std::vector< std::pair<int, int> > row5;
        std::pair<int, int> pair5 (5,6);
        row5.push_back(pair5);
        std::vector< std::pair<int, int> > row6;
        std::pair<int, int> pair6 (6,7);
        row6.push_back(pair6);
        std::vector< std::pair<int, int> > row7;
        std::pair<int, int> pair7 (7,8);
        row7.push_back(pair7);

        TS_ASSERT_EQUALS(
                smc.getRow(0),
                row0
                );
        TS_ASSERT_EQUALS(
                smc.getRow(1),
                row1
                );
        TS_ASSERT_EQUALS(
                smc.getRow(2),
                row2
                );
        TS_ASSERT_EQUALS(
                smc.getRow(3),
                row3
                );
        TS_ASSERT_EQUALS(
                smc.getRow(4),
                row4
                );
        TS_ASSERT_EQUALS(
                smc.getRow(5),
                row5
                );
        TS_ASSERT_EQUALS(
                smc.getRow(6),
                row6
                );
        TS_ASSERT_EQUALS(
                smc.getRow(7),
                row7
                );
    }

    // test with a 8x8 diagonal Matrix, C = 2; Sigma = 1
    // randome addPoints
    void testGetRow_three()
    {
//std::cout << "\n\n\nTEST 3: C=2 Sigma=1 Diagonalmatrix" <<std::endl;

        int const C (2);
        int const SIGMA (1);
        SellCSigmaSparseMatrixContainer<int, C, SIGMA> smc;

        /* add a test 8x8 Matrix:
         * 1 0 0 0 0 0 0 0
         * 0 2 0 0 0 0 0 0
         * 0 0 3 0 0 0 0 0
         * 0 0 0 4 0 0 0 0
         * 0 0 0 0 5 0 0 0
         * 0 0 0 0 0 6 0 0
         * 0 0 0 0 0 0 7 0
         * 0 0 0 0 0 0 0 8
         */

        smc.addPoint (5, 5, 6);
        smc.addPoint (1, 1, 2);
        smc.addPoint (4, 4, 5);
        smc.addPoint (2, 2, 3);
        smc.addPoint (0, 0, 1);
        smc.addPoint (6, 6, 7);
        smc.addPoint (7, 7, 8);
        smc.addPoint (3, 3, 4);

        std::vector< std::pair<int, int> > row0;
        std::pair<int, int> pair0 (0,1);
        row0.push_back(pair0);
        std::vector< std::pair<int, int> > row1;
        std::pair<int, int> pair1 (1,2);
        row1.push_back(pair1);
        std::vector< std::pair<int, int> > row2;
        std::pair<int, int> pair2 (2,3);
        row2.push_back(pair2);
        std::vector< std::pair<int, int> > row3;
        std::pair<int, int> pair3 (3,4);
        row3.push_back(pair3);
        std::vector< std::pair<int, int> > row4;
        std::pair<int, int> pair4 (4,5);
        row4.push_back(pair4);
        std::vector< std::pair<int, int> > row5;
        std::pair<int, int> pair5 (5,6);
        row5.push_back(pair5);
        std::vector< std::pair<int, int> > row6;
        std::pair<int, int> pair6 (6,7);
        row6.push_back(pair6);
        std::vector< std::pair<int, int> > row7;
        std::pair<int, int> pair7 (7,8);
        row7.push_back(pair7);

        TS_ASSERT_EQUALS(
                smc.getRow(0),
                row0
                );
        TS_ASSERT_EQUALS(
                smc.getRow(1),
                row1
                );
        TS_ASSERT_EQUALS(
                smc.getRow(2),
                row2
                );
        TS_ASSERT_EQUALS(
                smc.getRow(3),
                row3
                );
        TS_ASSERT_EQUALS(
                smc.getRow(4),
                row4
                );
        TS_ASSERT_EQUALS(
                smc.getRow(5),
                row5
                );
        TS_ASSERT_EQUALS(
                smc.getRow(6),
                row6
                );
        TS_ASSERT_EQUALS(
                smc.getRow(7),
                row7
                );
    }

    // test with a 8x8 diagonal Matrix, C = 2; Sigma = 1
    void testGetRow_fore()
    {
//std::cout << "\n\n\nTEST 4 C=3 Sigma=1 Diagonalmatrix sotiert" <<std::endl;
        int const C (3);
        int const SIGMA (1);
        SellCSigmaSparseMatrixContainer<int, C, SIGMA> smc;

        /* add a test 8x8 Matrix:
         * 1 0 0 0 0 0 0 0
         * 0 2 0 0 0 0 0 0
         * 0 0 3 0 0 0 0 0
         * 0 0 0 4 0 0 0 0
         * 0 0 0 0 5 0 0 0
         * 0 0 0 0 0 6 0 0
         * 0 0 0 0 0 0 7 0
         * 0 0 0 0 0 0 0 8
         */

        smc.addPoint (0, 0, 1);
        smc.addPoint (1, 1, 2);
        smc.addPoint (2, 2, 3);
        smc.addPoint (3, 3, 4);
        smc.addPoint (4, 4, 5);
        smc.addPoint (5, 5, 6);
        smc.addPoint (6, 6, 7);
        smc.addPoint (7, 7, 8);

        std::vector< std::pair<int, int> > row0;
        std::pair<int, int> pair0 (0,1);
        row0.push_back(pair0);
        std::vector< std::pair<int, int> > row1;
        std::pair<int, int> pair1 (1,2);
        row1.push_back(pair1);
        std::vector< std::pair<int, int> > row2;
        std::pair<int, int> pair2 (2,3);
        row2.push_back(pair2);
        std::vector< std::pair<int, int> > row3;
        std::pair<int, int> pair3 (3,4);
        row3.push_back(pair3);
        std::vector< std::pair<int, int> > row4;
        std::pair<int, int> pair4 (4,5);
        row4.push_back(pair4);
        std::vector< std::pair<int, int> > row5;
        std::pair<int, int> pair5 (5,6);
        row5.push_back(pair5);
        std::vector< std::pair<int, int> > row6;
        std::pair<int, int> pair6 (6,7);
        row6.push_back(pair6);
        std::vector< std::pair<int, int> > row7;
        std::pair<int, int> pair7 (7,8);
        row7.push_back(pair7);

        TS_ASSERT_EQUALS(
                smc.getRow(0),
                row0
                );
        TS_ASSERT_EQUALS(
                smc.getRow(1),
                row1
                );
        TS_ASSERT_EQUALS(
                smc.getRow(2),
                row2
                );
        TS_ASSERT_EQUALS(
                smc.getRow(3),
                row3
                );
        TS_ASSERT_EQUALS(
                smc.getRow(4),
                row4
                );
        TS_ASSERT_EQUALS(
                smc.getRow(5),
                row5
                );
        TS_ASSERT_EQUALS(
                smc.getRow(6),
                row6
                );
        TS_ASSERT_EQUALS(
                smc.getRow(7),
                row7
                );
    }

    // test with a 9x9 sparse Matrix, C = 3; Sigma = 1
    void testGetRow_five()
    {
//std::cout << "\n\n\nTEST 5 C=3 Sigma=1 sparse matrix" <<std::endl;
        int const C (3);
        int const SIGMA (1);
        SellCSigmaSparseMatrixContainer<char, C, SIGMA> smc;

        /* add a test 8x8 Matrix:
         *              col
         * row | 0 1 2 3 4 5 6 7 8     chunk #
         * ____|_______________________________
         *  0  | 0 0 0 0 A 0 0 0 0 |
         *  1  | 0 0 0 0 0 0 0 0 0 |-> chunk 0
         *  2  | 0 0 0 0 B 0 C 0 0 |
         * ----+-------------------------------
         *  3  | 0 0 D 0 0 0 0 E F |
         *  4  | G 0 0 0 0 H 0 0 0 |-> chunk 1
         *  5  | 0 I J 0 0 0 0 0 0 |
         * ----+-------------------------------
         *  6  | 0 0 0 K 0 0 0 0 0 |
         *  7  | L 0 M 0 N 0 O 0 P |-> chunk 2
         *  8  | 0 0 0 S 0 Q 0 R 0 |
         */

        smc.addPoint (4, 0, 'G');
        smc.addPoint (8, 7, 'R');
        smc.addPoint (6, 3, 'K');
        smc.addPoint (7, 6, 'O');
        smc.addPoint (7, 4, 'N');
        smc.addPoint (7, 2, 'M');
        smc.addPoint (0, 4, 'A');
        smc.addPoint (3, 8, 'F');
        smc.addPoint (7, 0, 'L');
        smc.addPoint (3, 7, 'E');
        smc.addPoint (2, 4, 'B');
        smc.addPoint (5, 1, 'I');
        smc.addPoint (7, 8, 'P');
        smc.addPoint (3, 2, 'D');
        smc.addPoint (8, 5, 'Q');
        smc.addPoint (8, 3, 'S');
        smc.addPoint (5, 2, 'J');
        smc.addPoint (4, 5, 'H');
        smc.addPoint (2, 6, 'C');

        std::vector< std::pair<int, char> > row0;
        std::pair<int, char> pair0 (4,'A');
        row0.push_back(pair0);

        std::vector< std::pair<int, char> > row1;

        std::vector< std::pair<int, char> > row2;
        std::pair<int, char> pair1 (4,'B');
        std::pair<int, char> pair2 (6,'C');
        row2.push_back(pair1);
        row2.push_back(pair2);

        std::vector< std::pair<int, char> > row3;
        std::pair<int, char> pair3 (2,'D');
        std::pair<int, char> pair4 (7,'E');
        std::pair<int, char> pair5 (8,'F');
        row3.push_back(pair3);
        row3.push_back(pair4);
        row3.push_back(pair5);

        std::vector< std::pair<int, char> > row4;
        std::pair<int, char> pair6 (0,'G');
        std::pair<int, char> pair7 (5,'H');
        row4.push_back(pair6);
        row4.push_back(pair7);

        std::vector< std::pair<int, char> > row5;
        std::pair<int, char> pair8 (1,'I');
        std::pair<int, char> pair9 (2,'J');
        row5.push_back(pair8);
        row5.push_back(pair9);

        std::vector< std::pair<int, char> > row6;
        std::pair<int, char> pair10 (3,'K');
        row6.push_back(pair10);

        std::vector< std::pair<int, char> > row7;
        std::pair<int, char> pair11 (0,'L');
        std::pair<int, char> pair12 (2,'M');
        std::pair<int, char> pair13 (4,'N');
        std::pair<int, char> pair14 (6,'O');
        std::pair<int, char> pair15 (8,'P');
        row7.push_back(pair11);
        row7.push_back(pair12);
        row7.push_back(pair13);
        row7.push_back(pair14);
        row7.push_back(pair15);

        std::vector< std::pair<int, char> > row8;
        std::pair<int, char> pair16 (5,'Q');
        std::pair<int, char> pair17 (7,'R');
        std::pair<int, char> pair18 (3,'S');
        row8.push_back(pair18);
        row8.push_back(pair16);
        row8.push_back(pair17);


        TS_ASSERT_EQUALS(
                smc.getRow(0),
                row0
                );
        TS_ASSERT_EQUALS(
                smc.getRow(1),
                row1
                );
        TS_ASSERT_EQUALS(
                smc.getRow(2),
                row2
                );
        TS_ASSERT_EQUALS(
                smc.getRow(3),
                row3
                );
        TS_ASSERT_EQUALS(
                smc.getRow(4),
                row4
                );
        TS_ASSERT_EQUALS(
                smc.getRow(5),
                row5
                );
        TS_ASSERT_EQUALS(
                smc.getRow(6),
                row6
                );
        TS_ASSERT_EQUALS(
                smc.getRow(7),
                row7
                );
        TS_ASSERT_EQUALS(
                smc.getRow(8),
                row8
                );
    }

};

}