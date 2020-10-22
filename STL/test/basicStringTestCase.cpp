#include "basicStringTestCase.h"

#include "basic_string.h"

namespace mySTL {
    void BasicStringTestCase::testAll() {
        printf("\nBasicStringTestCase start!\n");
        testCase1();
        testCase2();
        // testCase3();
        // testCase4();
        printf("BasicStringTestCase pass!\n");
    }

    void BasicStringTestCase::testCase1() {
        string str1("abc");
        string str2(str1);
        string str3 = str2;
        if (str1 != str2 || str2 != str3) {
            error_msg("BasicStringTestCase1 stage 1");
        }
        if (str2.length() != 3 || str3.length() != 3) {
            error_msg("BasicStringTestCase1 stage 2");
        }
        string str4(move(str1));
        if (str4.length() != 3 || str4 != str2 || str1.length() != 0) {
            error_msg("BasicStringTestCase1 stage 3");
        }

        string str5("abcdefghijklmnopqsrtuvwxyz");
        string str6(str5);
        string str7 = str6;
        if (str5 != str6 || str5 != str7) {
            error_msg("BasicStringTestCase1 stage 4");
        }
        if (str6.length() != 26 || str7.length() != 26) {
            error_msg("BasicStringTestCase1 stage 5");
        }
        string str8(move(str5));
        if (str8.length() != 26 || str8 != str6 || str5.length() != 0) {
            error_msg("BasicStringTestCase1 stage 6");
        }

        str2 = str6;
        if (str2.length() != 26 || str6 != str2) {
            error_msg("BasicStringTestCase1 stage 7");
        }

        str7 = str3;
        if (str7.length() != 3 || str7 != str3) {
            error_msg("BasicStringTestCase1 stage 8");
        }

        string str9("abcdefghijklmnopqrstuv");
        string str10(str9);
        string str11("abcdefghijklmnopqrs");
        string str12(str11);

        str9 = move(str11);

        if (str9 != str12 || str9.length() != 19 || str11.length() != 0) {
            error_msg("BasicStringTestCase1 stage 9");
        }
    }

    void BasicStringTestCase::testCase2() {
        string str1;
        string str2("abc");
        for (int i = 0; i < 5; ++i) {
            str1 += str2;
            str1 += "def";
        }
        if (str1.length() != 30 || str1 != "abcdefabcdefabcdefabcdefabcdef") {
            error_msg("BasicStringTestCase2 stage 1");
        }
    }


}  // namespace mySTL