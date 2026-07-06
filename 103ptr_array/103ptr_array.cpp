// 103ptr_array.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class XData
{
public:
	int x = 0;
	int y = 0;
};
#define ARRSIZE 3
int main()
{
	std::cout << "cppds.com" << endl;
	//栈二维数组初始化
	{
		// 2x3
		// 1 2 3
		// 4 5 6
		unsigned char arr1[2][ARRSIZE] = { {1,2,3},{4,5,6} };
		unsigned char arr2[][ARRSIZE] = {
			{1,2,3},
			{2,3,4},
			{3,4,5} };
		cout << "arr1[2][3] sizeof(arr1) = " << sizeof(arr1) << endl;
		cout << "arr2[][3] sizeof(arr2) = " << sizeof(arr2) << endl;

		int arr3[2][3][4] =
		{
			{{1,2,3,4},{2,3,4,5},{1,2,3,4}},
			{{1,2,3,4},{2,3,4,5},{1,2,3,4}},
		};
		int arr4[][3][4] =
		{
			{{1,2,3,4},{2,3,4,5},{1,2,3,4}},
			{{1,2,3,4},{2,3,4,5},{1,2,3,4}},
			{{1,2,3,4},{2,3,4,5},{1,2,3,4}},
		};
		for (auto arr : arr2)
		{
			for (int i = 0; i < ARRSIZE; i++)
			{
				cout << static_cast<int>(arr[i]) << " " << flush;
			}
			cout << endl;
		}
		int width = ARRSIZE;
		int height = sizeof(arr2) / (ARRSIZE * sizeof(unsigned char));

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				arr2[i][j]++;
				cout << (int)arr2[i][j] << "-" << flush;
			}
			cout << endl;
		}
	}

	//堆中二维数组的两种方式
	{
		//连续空间
		int size = 2;
		/*
		* “数量”只对应最外层数组的长度。把 new 后面的第一个 [] 当成“数量”，剩下的部分就是“元素类型”。
		* new int[size][3]
		*
		* 可以按照 new[] 的通用形式来理解：
		*
		*     new 元素类型[数量]
		*
		* 对于 new int[size][3] 来说：
		*
		*     元素类型 = int[3]
		*     数量     = size
		*
		* 也就是说，它创建的不是 size * 3 个零散的 int 指针，
		* 而是创建了 size 个 int[3] 类型的数组元素。
		*
		* 等价理解：
		*
		*     new int[size][3]
		*
		* 创建的是：
		*
		*     arr5[0]  -> int[3]
		*     arr5[1]  -> int[3]
		*     arr5[2]  -> int[3]
		*     ...
		*     arr5[size - 1] -> int[3]
		*
		* new[] 返回的是指向第一个元素的指针。
		*
		* 第一个元素的类型是：
		*
		*     int[3]
		*
		* 所以返回值类型是：
		*
		*     int (*)[3]
		*
		* 含义是：
		*
		*     指向“含有 3 个 int 的数组”的指针
		*
		* 因此接收这个返回值时，应该写成：
		*
		*     int (*arr5)[3]
		*
		* 而不是 int**。
		*
		* 注意：
		*
		*     int (*arr5)[3]
		*
		* 表示 arr5 是一个指针，指向 int[3]。
		*
		* 初始化部分：
		*
		*     { {1,1,2}, {3,2,3} }
		*
		* 表示初始化前两行：
		*
		*     arr5[0] = {1, 1, 2}
		*     arr5[1] = {3, 2, 3}
		*
		* 如果 size > 2，剩余的行会被值初始化，
		* 对 int 来说就是初始化为 0。
		*
		* 例如 size == 4 时：
		*
		*     arr5[0] = {1, 1, 2}
		*     arr5[1] = {3, 2, 3}
		*     arr5[2] = {0, 0, 0}
		*     arr5[3] = {0, 0, 0}
		*
		* 释放时使用：
		*
		*     delete[] arr5;
		*/
		int (*arr5)[3] = new int[size][3]{
			{1, 1, 2},
			{3, 2, 3}
		};
		for (int i = 0; i < size; i++)
		{
			//sizeof(arr5[i]) 12 ;
			for (auto a : arr5[i])
			{
				cout << a << "=";
			}
			cout << endl;
		}
		delete[]arr5;
		arr5 = nullptr;

		int width = 4;
		int height = 3;
		//指针数组
		/*
		1 2 3 1
		4 5 6 3
		1 1 1 1
		*/

		/*
		* “数量”只对应最外层数组的长度。把 new 后面的第一个 [] 当成“数量”，剩下的部分就是“元素类型”。
		* new int*[height] {0}
		*
		* 可以按照 new[] 的通用形式来理解：
		*
		*     new 元素类型[数量] {初始化值}
		*
		* 对于 new int*[height] {0} 来说：
		*
		*     元素类型 = int*
		*     数量     = height 
		*
		* 也就是说，它创建的是 height 个 int* 类型的元素，
		* 也就是一个“指针数组”。
		*
		* 等价理解：
		*
		*     arr6[0]  -> int*
		*     arr6[1]  -> int*
		*     arr6[2]  -> int*
		*     ...
		*     arr6[height - 1] -> int*
		*
		* new[] 返回的是指向第一个元素的指针。
		*
		* 第一个元素的类型是：
		*
		*     int*
		*
		* 所以返回值类型是：
		*
		*     int**
		*
		* 含义是：
		*
		*     指向 int* 的指针
		*
		* 因此接收这个返回值时，应该写成：
		*
		*     int** arr6
		*
		* 初始化部分：
		*
		*     {0}
		*
		* 表示把数组中的指针元素初始化为空指针。
		*
		* 对于指针类型来说，0 可以作为空指针常量使用。
		* 所以 new int*[height] {0} 之后：
		*
		*     arr6[0] = nullptr
		*     arr6[1] = nullptr
		*     arr6[2] = nullptr
		*     ...
		*     arr6[height - 1] = nullptr
		*
		* 更推荐的现代 C++ 写法是：
		*
		*     new int*[height] {}
		*
		* 或者：
		*
		*     new int*[height] {nullptr}
		*
		* 注意：
		*
		*     int** arr6 = new int*[height] {0};
		*
		* 这一步只创建了外层的指针数组，
		* 也就是 height 个 int*。
		*
		* 它还没有给每一行分配 int 数组空间。
		* 此时 arr6[i] 都是空指针，不能直接访问 arr6[i][j]。
		*
		* 如果要创建 height 行、width 列的二维动态数组，
		* 还需要继续给每一行分配空间：
		*
		*     for (int i = 0; i < height; ++i) {
		*         arr6[i] = new int[width] {};
		*     }
		*
		* 释放时也要分两层释放：
		*
		*     for (int i = 0; i < height; ++i) {
		*         delete[] arr6[i];
		*     }
		*
		*     delete[] arr6;
		*/
		int** arr6 = new int* [height] {0};
		for (int i = 0; i < height; i++)
		{
			arr6[i] = new int[width] {0};
		}
		arr6[1][1] = 99;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << arr6[i][j] << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < height; i++) {
			delete[] arr6[i];
			arr6[i] = nullptr;
		}

		delete[] arr6;
		arr6 = nullptr;

	}
	getchar();

	// 栈空间 未初始化数组 空间内部不定
	int arr1[10]; //
	cout << "sizeof(arr1) = " << sizeof(arr1) << endl;
	memset(arr1, 0, sizeof(arr1)); //数组可以通过sizeof获取内存大小
	int arr2[5] = { 1,2,3,4,5 };
	int arr3[32] = { 1,2,3 };
	int arr4[1024] = { 0 }; //全部设置为0
	int arr5[] = { 1,2,3,4 };
	char str1[] = "test001";
	cout << "sizeof(arr5) = " << sizeof(arr5) << endl;
	cout << "sizeof(str1) = " << sizeof(str1) << endl;
	for (auto s : str1) //只能访问数组
	{
		cout << s << "-" << flush;
	}
	cout << endl;

	cout << "&arr2[0] = " << &arr2[0] << endl;
	cout << "&arr2[1] = " << &arr2[1] << endl;
	cout << "arr2+2 = " << arr2 + 2 << endl;
	//std::begin(arr1);
	//std::end(arr1);
	std::find(std::begin(arr5), std::end(arr5), 3);

	//堆空间
	int* parr1 = new int[1024];
	int psize = 2048;
	auto parr2 = new unsigned char[psize];
	//int tmp[psize];//????
	memset(parr2, 0, psize);
	auto parr3 = new int[psize];
	memset(parr3, 0, psize * sizeof(int));  //sizeof(parr3)??? 32=>4 64=>8
	//for(auto s:parr2)
	int* parr4 = new int[3] { 1, 2, 3 };
	int* parr5 = new int[] { 1, 2, 3, 6 };
	int* parr6 = new int[] { 0 };

	cout << "parr5[2] = " << parr5[2] << endl;
	cout << "*(parr5+3) = " << *(parr5 + 3) << endl;
	cout << "&parr5[0] = " << &parr5[0] << endl;
	cout << "&parr5[1] = " << &parr5[1] << endl;
	cout << "parr5+2 = " << parr5 + 2 << endl;

	delete[] parr1;
	parr1 = nullptr; //NULL 0
	delete[] parr2;
	parr2 = nullptr;
	delete[] parr3;
	parr3 = nullptr;
	delete[] parr4;
	parr4 = nullptr;
	delete[] parr5;
	parr5 = nullptr;
	delete[] parr6;
	parr6 = nullptr;
	XData* datas = new XData[1024];
	delete[] datas;
	datas = nullptr;

	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
