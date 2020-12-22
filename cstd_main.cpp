#include <iostream>
#include <array>
#include <vector>

using namespace std;

// Forward declaration
void execute_STL_Array();
void execute_STL_Vector();

template<typename T, size_t N>
void test_std_array_iterators(std::array<T,N>&);

// Main Entry 
int main(int argc, char *argv[])
{
BEGIN:
    cout << "This executable tests all the C++ Standard(STL) library functionalities:" << endl;
    cout << "1. Array" << endl;
    cout << "2. Vector" << endl;
    
    uint16_t input = 0;
    cout << "\n\nSelect CSTD case to run: ";    
    if (argc == 1)
    {
        // No argument entered by user
        cin >> input;
    } else
    {
        // user directly entered argument via argv
        input = atoi(argv[1]);
        cout << input << " " << endl;
        cout << "argc = " << argc << " argv[1] = " << argv[1] << " input = " << input << endl;
    }
    
    switch (input)
    {
        case 1:
        {
            (void)execute_STL_Array();
            break;
        }
        case 2:
        {
            (void)execute_STL_Vector();
            break;
        }
        default:
            cout << "Invalid input!" << endl << endl;
            goto BEGIN; 
    }
    return 0;
}

// Theoretically I want to output any std::array type here
template<typename T, size_t N>
void output_whole_std_array(std::array<T,N>& arrayPtr, string OutputTag)
{
    cout << OutputTag << " = ";
    // Way 1: Using iterator to loop thru
    // for (auto& ptr_iterator : arrayPtr)
    // {
    //     cout << ptr_iterator << " " ;
    // }

    // Way 2: 
    // Using .at to loop
    // for (auto i=0; i < arrayPtr.size(); i++)
    // {
    //     cout << arrayPtr.at(i) << " ";
    // }

    // Way 3: 
    // Using [] operator to loop
    for (uint8_t i=0; i < arrayPtr.size(); i++)
    {
        cout << arrayPtr[i] << " ";
    }    
    cout << endl;
}

// Display size of an std::array
template<typename T, size_t N>
void output_std_array_size(std::array<T,N>& arrayPtr, string OutputTag)
{
    cout << OutputTag << " size = " << arrayPtr.size() << endl;
}

// Front(), Back() and Data()
template<typename T, size_t N>
void test_front_back_and_data(std::array<T,N>* inputPtr)
{
    cout << "Front of increasing_array = " << inputPtr->front() 
         << " , Back = " << inputPtr->back() << endl;

    // this gives you inputPtr[0] and inputPtr[1]
    cout << inputPtr->data()[0] << " , " << inputPtr->data()[1] << endl;
}

/*************************************************************************
 * std::array<T,N> behaviors used by Richard
 * at(), [] operator, front(), back(), data(),
 * begin()\cbegin(), end()\cend(), rbegin()\crbegin(), rend()\crend()
 * empty(), size(), max_size(), fill(), swap(), get()
 * **********************************************************************/
void execute_STL_Array()
{
    // operator = will copy every element of the warray with element of another array
    constexpr uint8_t int16ArraySize = 10;
    std::array<int16_t, int16ArraySize> int16ArrayOriginal = {0};
    std::array<int16_t, int16ArraySize> int16ArraySwapped  = {5};

    // Display initialization values:
    cout << "Default initialization values:" << endl;
    output_std_array_size(int16ArrayOriginal, "int16ArrayOriginal");
    output_whole_std_array(int16ArrayOriginal, "int16ArrayOriginal");
    output_std_array_size(int16ArraySwapped, "int16ArraySwapped");    
    output_whole_std_array(int16ArraySwapped,  "int16ArraySwapped");

    // Using fill to do initialization
    int16ArrayOriginal.fill(10);
    int16ArraySwapped.fill(20);

    cout << "After filled:" << endl;
    output_whole_std_array(int16ArrayOriginal, "int16ArrayOriginal filled: ");
    output_whole_std_array(int16ArraySwapped,  "int16ArraySwapped filled: ");

    // Test .front() & .back() & .data()
    std::array<int, 10> increasing_array;
    cout << "increasing array = ";
    for (auto i = 0; i < increasing_array.size(); i++)
    {
        increasing_array.at(i) = i+5;
        cout << increasing_array.at(i) << " ";
    }
    test_front_back_and_data(&increasing_array);

    // Begin/CBegin and End/CEnd
    int begin = 0, end = 0;
    begin = *(increasing_array.begin());
    end   = *(increasing_array.end());

    cout << "Begin = " << begin << " End = " << *(increasing_array.end()) << endl;
    cout << "CBegin = " << *(increasing_array.cbegin()) << " CEnd = " << *(increasing_array.cend()) << endl;

    // RBegin/CRBegin and REnd/CREnd

    // empty or not, basically check if begin() == end()
    std::array<int, 0> no_numbers;
    cout << "is increasing_array empty? " << increasing_array.empty() << endl;
    cout << "max_size of increasing_array = " << increasing_array.max_size() << endl;  
    cout << "is no_numbers empty? " << no_numbers.empty() << endl;
    cout << "max_size of no_numbers = " << no_numbers.max_size() << endl;

    // For std::array max_size and size are equal due to it must be fixed size array
    std::array<int, 10> half_numbers = {1,2,3,4,5};
    cout << "max_size of half_numbers = " << half_numbers.max_size() << endl;
    cout << "size of half_numbers = "     << half_numbers.size() << endl;

    // Copy operator
    half_numbers = increasing_array;
    output_whole_std_array(half_numbers, "Copied half_numbers");

    // get() which fetches the elements of an array
    std::get<5>(half_numbers) = 30;
    std::get<7>(half_numbers) = 50;
    std::get<9>(half_numbers) = 80;        
    cout << "half_numbers[5] = " << std::get<5>(half_numbers) << endl;
    output_whole_std_array(half_numbers, "Modified half_numbers");

    // swap(array1, array2) will interchange the contents within, size must match between the two due to std::is_swappable<T> needs to be true
    std::swap(half_numbers, increasing_array);
    output_whole_std_array(half_numbers, "Swapped half_numbers"); 
    output_whole_std_array(increasing_array, "Swapped increasing_array");

    // Test copy operator
    std::array<int, 10> test_array1;
    test_array1 = increasing_array;

    // Play with iterators
    std::array<uint32_t, 15> input1;
    for (auto i = 0; i < input1.size(); i++)
    {
        input1.at(i) = i * 3;
    }
    test_std_array_iterators(input1);
    return;
}

template<typename T, size_t N>
void test_std_array_iterators(std::array<T,N>& arrayPtr)
{
    output_whole_std_array(arrayPtr, "test_std_array_iterators arrayPtr");

    // use auto iterator to display values, iterators are basically the pointer to each element and can be displayed or altered directly
    cout << "Using iterators to display: ";
    for (auto it = arrayPtr.begin(); it < arrayPtr.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Let's multiply first half of arrayPtr with 10, and second half with 1000 
    for (auto it = arrayPtr.begin(); it < arrayPtr.end() - (arrayPtr.size()/2); it++)
    {
        *it *= 10;
    }
    for (auto it = arrayPtr.begin() + arrayPtr.size()/2; it < arrayPtr.end(); it++)
    {
        *it *= 1000;
    }
    output_whole_std_array(arrayPtr, "test_std_array_iterators arrayPtr after multipley 10 & 1000 ");

    // Let's play with rbegin/rend
    // Richard: Interestingly, the iterator starts at last element, and use it++ to move towards first element(rEnd())
    //           0      1 .........   N
    // rend() rend()+1  <----------- rBegin()
    arrayPtr.fill(0);
    for (auto it = arrayPtr.rbegin(); it < arrayPtr.rend(); it++)
    {
        *it = *it + 5;
    }
    output_whole_std_array(arrayPtr, "test_std_array_iterators arrayPtr using rend/begin ");

    // CEnd/CrEnd & CBegin/CrBegin
    for (auto it = arrayPtr.cbegin(); it < arrayPtr.cend(); it++)
    {
        // This won't compile because cbegin and cend are constant iterators. Only for reading!
        // *it = 1;
    }
}

/***********************************************
 * STL Vector:
 * Element access: at(), [] operator, assign(), front()/back(), data()
 * Iterator access: begin()/end(), rbegin()/rend()
 * Capacity: empty(), size(), max_size(), reserve(), capacity(), shrink_to_fit()
 * Modifiers: clear(), insert(), emplace(), erase(), push_back(), emplace_back(), pop_back(),
 *            resize(), swap()
 ************************************************/
template<typename T>
void output_std_vector(std::vector<T>& vec, string output_tag)
{
    cout << output_tag << " = ";
    for (auto it = vec.begin(); it < vec.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void execute_STL_Vector()
{
    std::vector<int> v = {0,1,2,3,4,5};
    // 100.0f 100.0f 100.0f
    std::vector<float> f(3, 100.0f);
    output_std_vector(v, "execute_STL_Vector v");
    output_std_vector(f, "execute_STL_Vector f");
    // assign can work like std::array.fill()
    f.assign(f.size(), 999.0f);
    output_std_vector(f, "execute_STL_Vector f assigned");

    // v[3] = 2 + 5 = 7
    v.at(3) = v.at(2) + v.at(v.size()-1);
    // v[0] = 0 + 5 = 5    
    v[0] = v.front() + v.back();
    // v.at(20) = 0; // This compiles and crashes but shouldn't at() does range bound check?? Ans: need to use try/catch to get exception
    // 5 1 2 7 4 5
    output_std_vector(v, "execute_STL_Vector updated 1");

    // Test capacity:
    if (!v.empty())
    {
        // Here the test result will show, size = 6, max_size = 2305843009213693951(basically the system free memory)
        // capacity = 6. But after reserve(50), capacity will = 50. Then after shrink_to_fit, capacity = 6 again.
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;
        v.reserve(50);
        cout << "reserve size = 50 " << endl;
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;
        v.shrink_to_fit();
        cout << "v.shrink_to_fit() ..." << endl;
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;
    }

    // test modifier:
    // Modifiers: clear(), insert(), emplace(), erase(), push_back(), emplace_back(), pop_back(),
    //            resize(), swap()
    if (!v.empty())
    {
        // This will clean the vector and size = 0, capacity = 6
        v.clear();
        output_std_vector(v, "execute_STL_Vector v.clear()");
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;        

        // resize will expand vector to [10] elements with values = 0, capacity = 10
        v.resize(10);
        output_std_vector(v, "execute_STL_Vector v.resize()");
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;        

        v.push_back(77);
        v.pop_back();
        v.push_back(99);
        // 0 0 0 0 0 0 0 0 0 0 99
        output_std_vector(v, "execute_STL_Vector v.push_back()/pop_back = ");        
    }

    // modifer part2: insert(), emplace(), erase(), emplace_back()
    if (!v.empty())
    {
        v.clear();
        v.resize(12);
        for (auto i = 0; i < v.size(); i++)
        {
            v.at(i) = i;
        }
        output_std_vector(v, "modifer 2 input");

        // test insert()
        auto it = v.begin();
        // -100, 0, 1, 2, 3, 4, 5, 7 ... 11
        v.insert(it, -100);
        output_std_vector(v, "modifer 2 insert 1");        
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;        

        // insert a -999 in the middle of vector
        v.insert(v.begin()+v.size()/2, -999);
        output_std_vector(v, "modifer 2 insert 2");           
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;        

        // insert 3 x -777 at end of the vector
        v.insert(v.end(), 3, -777);
        output_std_vector(v, "modifer 2 insert 3");           
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl; 

        // insert a vector into another vector
        std::vector<int> short_vec = {39, 39, 889, 1314};
        v.insert(v.end() - v.size()/2, short_vec.begin(), short_vec.end());
        output_std_vector(v, "modifer 2 insert 3");           
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl; 
    }

    // test erase
    // erase can also erase any range specified by iterator
    if (!v.empty())
    {
        // erase first half
        v.erase(v.begin(), v.begin() + v.size()/2);
        output_std_vector(v, "modifer 2 erase 1");           
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;         

        v.shrink_to_fit();        
        v.erase(v.begin(), v.end());
        output_std_vector(v, "modifer 2 erase 2");           
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;
    }

    // test emplace and emplace_back
    // std::vector::insert copies or moves the elements into the container by
    //  calling copy constructor or move constructor.
    // while, In std::vector::emplace elements are constructed in-place, 
    // i.e. no copy or move operations are performed.

    // URL: https://www.itread01.com/content/1543490413.html
    // If copy of an inserted object is non-trivial, then emplace needs to be used which constructs the item by calling new
    v.clear();
    v.resize(12);
    for (auto i = 0; i < v.size(); i++)
    {
        v.at(i) = i;
    }
    output_std_vector(v, "modifer 2 emplace input");    
    if (!v.empty())
    {
        v.emplace(v.end() - v.size()/2, -666);
        output_std_vector(v, "modifer 2 emplace 1");           
        cout << "vec size = " << v.size() << " max_size = " << v.max_size() << " capacity = " << v.capacity() << endl;        
    }
}