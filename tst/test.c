// gtest is normaly for C++ but can used for C as well.
// #include <gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensemble.h"



// NOt working yet.
// // Test if this file is working.
// TEST(test, test1) {
//     printf("Works\n");
//     // ASSERT_EQ(0,0);
// }

// Test for the init_infos function.
// TEST(ensemble, init_infos) {
//     struct positions_info infos;
//     init_infos(&infos);
//     int a = 0;
//     int b = HEIGHT-1;
//     for (int i = 0; i < HEIGHT ; ++i) {
//         printf("%d = %d\n",b ,infos.current_pieces_BLACK[i]);
//         printf("%d = %d\n",a ,infos.current_pieces_WHITE[i]);
//         // ASSERT_EQ(b, infos.current_pieces_BLACK[i]);
//         // ASSERT_EQ(a, infos.current_pieces_WHITE[i]);
//         a = a + HEIGHT;
//         b = b + HEIGHT;
//     }
//     // ASSERT_EQ(WORLD_SIZE, infos.MAX_TURNS);
//     // ASSERT_EQ(0, infos.TURNS);
// }
