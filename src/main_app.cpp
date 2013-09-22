#include "main.hh"

using namespace std;
using namespace Learning;

int
main(int argc, char** argv)
{
    cout << "MAIN APPRENTISSAGE" << endl;
    cout << "------------------" << endl;

    if (argc < 2)
    {
	cout << "[Usage] : " << argv[0] << " {filename}.txt" << endl;
	return -1;
    }

    list<Sign*> listSign;
    listSign = parse(argv[1]);



    // #####################################





	Sign s1("U");
	Sign s2("I");
	Sign s3("L");
	Sign s4("U");

	VecParam v1(1, 1, 1, 1, 1, 1, 1);
	VecParam v2(2, 2, 2, 2, 2, 2, 2);
	VecParam v3(3, 3, 3, 3, 3, 3, 3);
	VecParam v4(4, 4, 4, 4, 4, 4, 4);
	VecParam v5(5, 5, 5, 5, 5, 5, 5);
	VecParam v6(6, 6, 6, 6, 6, 6, 6);
	VecParam v7(7, 7, 7, 7, 7, 7, 7);
	VecParam v8(8, 8, 8, 8, 8, 8, 8);
	VecParam v9(9, 9, 9, 9, 9, 9, 9);
	VecParam v10(10, 10, 10, 10, 10, 10, 10);
	VecParam v11(11, 11, 11, 11, 11, 11, 11);
	VecParam v12(12, 12, 12, 12, 12, 12, 12);
	VecParam v13(13, 13, 13, 13, 13, 13, 13);
	VecParam v14(14, 14, 14, 14, 14, 14, 14);
	VecParam v15(15, 15, 15, 15, 15, 15, 15);
	VecParam v16(16, 16, 16, 16, 16, 16, 16);
	VecParam v17(17, 17, 17, 17, 17, 17, 17);
	VecParam v18(18, 18, 18, 18, 18, 18, 18);
	VecParam v19(19, 19, 19, 19, 19, 19, 19);
	VecParam v20(20, 20, 20, 20, 20, 20, 20);
	VecParam v21(21, 21, 21, 21, 21, 21, 21);
	VecParam v22(22, 22, 22, 22, 22, 22, 22);
	VecParam v23(23, 23, 23, 23, 23, 23, 23);
	VecParam v24(24, 24, 24, 24, 24, 24, 24);
	VecParam v25(25, 25, 25, 25, 25, 25, 25);
	VecParam v26(26, 26, 26, 26, 26, 26, 26);
	VecParam v27(27, 27, 27, 27, 27, 27, 27);
	VecParam v28(28, 28, 28, 28, 28, 28, 28);
	VecParam v29(29, 29, 29, 29, 29, 29, 29);
	VecParam v30(30, 30, 30, 30, 30, 30, 30);
	VecParam v31(31, 31, 31, 31, 31, 31, 31);
	VecParam v32(32, 32, 32, 32, 32, 32, 32);
	VecParam v33(33, 33, 33, 33, 33, 33, 33);
	VecParam v34(34, 34, 34, 34, 34, 34, 34);
	VecParam v35(35, 35, 35, 35, 35, 35, 35);
	VecParam v36(36, 36, 36, 36, 36, 36, 36);
	VecParam v37(37, 37, 37, 37, 37, 37, 37);
	VecParam v38(38, 38, 38, 38, 38, 38, 38);
	VecParam v39(39, 39, 39, 39, 39, 39, 39);
	VecParam v40(40, 40, 40, 40, 40, 40, 40);
	VecParam v41(41, 41, 41, 41, 41, 41, 41);
	VecParam v42(42, 42, 42, 42, 42, 42, 42);
	VecParam v43(43, 43, 43, 43, 43, 43, 43);
	VecParam v44(44, 44, 44, 44, 44, 44, 44);
	VecParam v45(45, 45, 45, 45, 45, 45, 45);
	VecParam v46(46, 46, 46, 46, 46, 46, 46);
	VecParam v47(47, 47, 47, 47, 47, 47, 47);
	VecParam v48(48, 48, 48, 48, 48, 48, 48);
	VecParam v49(49, 49, 49, 49, 49, 49, 49);
	VecParam v50(50, 50, 50, 50, 50, 50, 50);
	VecParam v51(51, 51, 51, 51, 51, 51, 51);

	s1.add_data(v1);
	s1.add_data(v2);
	s1.add_data(v3);
	s1.add_data(v4);
	s1.add_data(v5);
	s1.add_data(v6);
	s1.add_data(v7);
	s1.add_data(v8);
	s1.add_data(v9);
	s1.add_data(v10);
	s1.add_data(v11);
	s1.add_data(v12);
	s1.add_data(v13);
	s1.add_data(v14);
	s1.add_data(v15);
	s1.add_data(v16);
	s1.add_data(v17);
	s1.add_data(v18);
	s1.add_data(v19);
	s1.add_data(v20);
	s1.add_data(v21);
	s1.add_data(v22);
	s1.add_data(v23);
	s1.add_data(v24);
	s1.add_data(v25);
	s1.add_data(v26);
	s1.add_data(v27);
	s1.add_data(v28);
	s1.add_data(v29);
	s1.add_data(v30);
	s1.add_data(v31);
	s1.add_data(v32);
	s1.add_data(v33);
	s1.add_data(v34);
	s1.add_data(v35);
	s1.add_data(v36);
	s1.add_data(v37);
	s1.add_data(v38);
	s1.add_data(v39);
	s1.add_data(v40);
	s1.add_data(v41);
	s1.add_data(v42);
	s1.add_data(v43);
	s1.add_data(v44);
	s1.add_data(v45);
	s1.add_data(v46);
	s1.add_data(v47);
	s1.add_data(v48);
	s1.add_data(v49);
	s1.add_data(v50);



	s4.add_data(v1);
	s4.add_data(v2);
	s4.add_data(v3);
	s4.add_data(v4);
	s4.add_data(v5);
	s4.add_data(v6);
	s4.add_data(v7);
	s4.add_data(v8);
	s4.add_data(v9);
	s4.add_data(v10);
	s4.add_data(v11);
	s4.add_data(v12);
	s4.add_data(v13);
	s4.add_data(v14);
	s4.add_data(v15);
	s4.add_data(v16);
	s4.add_data(v17);
	s4.add_data(v18);
	s4.add_data(v19);
	s4.add_data(v20);
	s4.add_data(v21);
	s4.add_data(v22);
	s4.add_data(v23);
	s4.add_data(v24);
	s4.add_data(v25);
	s4.add_data(v26);
	s4.add_data(v27);
	s4.add_data(v28);
	s4.add_data(v29);
	s4.add_data(v30);
	s4.add_data(v31);
	s4.add_data(v32);
	s4.add_data(v33);
	s4.add_data(v34);
	s4.add_data(v35);
	s4.add_data(v36);
	s4.add_data(v37);
	s4.add_data(v38);
	s4.add_data(v39);
	s4.add_data(v40);
	s4.add_data(v41);
	s4.add_data(v42);
	s4.add_data(v43);
	s4.add_data(v44);
	s4.add_data(v45);
	s4.add_data(v46);
	s4.add_data(v47);
	s4.add_data(v48);
	s4.add_data(v49);
	s4.add_data(v51);


	s2.add_data(v4);
	s2.add_data(v5);
	s2.add_data(v6);

	s3.add_data(v1);
	s3.add_data(v2);
	s3.add_data(v3);
	s3.add_data(v4);
	s3.add_data(v5);
	s3.add_data(v6);
	s3.add_data(v7);
	s3.add_data(v8);
	s3.add_data(v9);
	s3.add_data(v10);
	s3.add_data(v11);
	s3.add_data(v12);
	s3.add_data(v13);
	s3.add_data(v14);
	s3.add_data(v15);
	s3.add_data(v16);
	s3.add_data(v17);
	s3.add_data(v18);
	s3.add_data(v19);
	s3.add_data(v20);
	s3.add_data(v21);
	s3.add_data(v22);
	s3.add_data(v23);
	s3.add_data(v24);
	s3.add_data(v25);
	s3.add_data(v26);
	s3.add_data(v27);
	s3.add_data(v28);
	s3.add_data(v29);
	s3.add_data(v30);
	s3.add_data(v31);
	s3.add_data(v32);
	s3.add_data(v33);
	s3.add_data(v34);
	s3.add_data(v35);
	s3.add_data(v36);
	s3.add_data(v37);
	s3.add_data(v38);
	s3.add_data(v39);
	s3.add_data(v40);


	//s1.normalize();
	//s4.normalize();
	//
	//list<Sign*> list;(&s1, &s4);
	//list.push_back(&s1);
	//list.push_back(&s4);
	//
	//Model m("U", list);


	//Base b = make_base(list);



    //  ######################################



	Base b = make_base(listSign);


	write_base(b);



    cout << "------------------" << endl;

    return 0;
}
