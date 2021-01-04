#include <iostream>
#include <string>

// STL container headers
#include <array>
#include <deque>
#include <vector>
#include <forward_list>
#include <list>
#include <queue>  // include std::queue and std::priority_queue type

using namespace std;

// Macro definition
// #define FULL_COMPILE_SPEED

// Forward declaration
void execute_STL_Array();
void execute_STL_Vector();
void execute_STL_Deque();
void execute_STL_Forward_List();
void execute_STL_List();
void execute_STL_Queue();
void execute_STL_Priority_Queue();

template<typename T, size_t N>
void test_std_array_iterators(std::array<T,N>&);

// Main Entry 
int main(int argc, char *argv[])
{
BEGIN:
    // Q S H A L V
    cout << "This executable tests all the C++ Standard(STL) library functionalities:" << endl;
    cout << "1. Array" << endl;
    cout << "2. Vector" << endl;
    cout << "3. Deque" << endl;
    cout << "4. Forward_list" << endl;
    cout << "5. List" << endl;
    cout << "6. Queue" << endl;
    cout << "7. Priority_Queue" << endl;
    
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
        case 3:
        {
            (void)execute_STL_Deque();
            break;
        }
        case 4:
        {
            (void)execute_STL_Forward_List();
            break;
        }       
        case 5:
        {
            (void)execute_STL_List();
            break;
        }
        case 6:
        {
            (void)execute_STL_Queue();
            break;
        }
        case 7:
        {
            (void)execute_STL_Priority_Queue();
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
#ifdef FULL_COMPILE_SPEED
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
#endif
    return;
}

template<typename T, size_t N>
void test_std_array_iterators(std::array<T,N>& arrayPtr)
{
#ifdef FULL_COMPILE_SPEED
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
#endif
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
    for (typename std::vector<T>::iterator it = vec.begin(); it < vec.end(); advance(it,1))
    {
        cout << *it << " ";
    }

    cout << endl;
}

void execute_STL_Vector()
{
#ifdef FULL_COMPILE_SPEED
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
#endif
}

/***********************************************
 * STL Deque:
 * deque (usually pronounced like "deck") is an irregular acronym of double-ended queue. Double-ended queues are sequence containers with
 *  dynamic sizes that can be expanded or contracted on both ends (either its front or its back).
 *  Specific libraries may implement deques in different ways, generally as some form of dynamic array. 
 *  But in any case, they allow for the individual elements to be accessed directly through random access iterators, with storage handled
 *  automatically by expanding and contracting the container as needed.
 * Therefore, they provide a functionality similar to vectors, but with efficient insertion and deletion of elements
 *  also at the beginning of the sequence, and not only at its end. But, unlike vectors, deques are not guaranteed to store all its elements
 *  in contiguous storage locations: accessing elements in a deque by offsetting a pointer to another element causes undefined behavior. 
 * Both vectors and deques provide a very similar interface and can be used for similar purposes, 
 * but internally both work in quite different ways: While vectors use a single array that needs to be occasionally reallocated for growth,
 *  the elements of a deque can be scattered in different chunks of storage, with the container keeping the necessary information internally
 *  to provide direct access to any of its elements in constant time and with a uniform sequential interface (through iterators). 
 * Therefore, deques are a little more complex internally than vectors, but this allows them to grow more efficiently under certain circumstances,
 *  especially with very long sequences, where reallocations become more expensive.

For operations that involve frequent insertion or removals of elements at positions other than the beginning or the end, deques perform worse and have less consistent iterators and references than lists and forward lists.
 * Element access: at(), [] operator, assign(), front()/back()
 * Iterator access: begin()/end(), rbegin()/rend()
 * Capacity: empty(), size(), resize(), max_size(),  shrink_to_fit()
 * Modifiers: clear(), insert(), emplace()/emplace_front()/emplace_back(), erase(), push_back()/push_front(),  pop_front/pop_back(),
 *            swap()
 ************************************************/
template<typename T>
void output_std_deque(std::deque<T>& myDeq, string output_tag)
{
    // Use iterator to display all
    cout << output_tag << " = ";
    /* for (auto it = myDeq.begin(); it < myDeq.end(); advance(it, 1))
    {
        cout << *it << " ";
    } */
    for (auto i = 0; i < myDeq.size(); i++)
    {
        cout << myDeq.at(i) << " ";
    }
    cout << endl;
}

void execute_STL_Deque()
{
    std::deque<string> myDeq;
    for (auto i = 0; i < 10; i++)
    {
        myDeq.push_back(to_string(i));
    }

    output_std_deque(myDeq, "myDeq input");

    // Element access: at(), [] operator, assign(), front()/back()
    cout << "myDeq[3] = " << myDeq[3] << endl;;
    cout << "myDeq.at(6) = " << myDeq.at(6) << endl;

    // myDeq will be replaced with 10 Hello_World
    // assign() has 3 overloads:
    // 1. Range: assign(Iterator_first, iterator_last)
    // 2. Fill:  assign(count, value)
    // 3. initializer:  assign(initializer_list<value_type> il),  
    //                 the new contents are copies of the values passed as initializer list, in the same order.
    std::deque<string> copiedDeq{"a", "b", "c", "1", "2", "3"};
    myDeq.assign(copiedDeq.begin(), copiedDeq.end()); // 1. Range via iterator
    output_std_deque(myDeq, "1. Range via iterator");    
    myDeq.clear();

    myDeq.assign(10, "Hello_World!");  // 2. Fill assign with 10x Hello_World
    output_std_deque(myDeq, "2. Fill assign");    
    myDeq.clear();

    myDeq.assign({"9", "8", "7", "6", "5"});  // 3. Initializer list
    output_std_deque(myDeq, "3. Initializer list");
    
    cout << "front = " << myDeq.front() << " back = " << myDeq.back() << endl;

    // Iterator access: begin()/end(), rbegin()/rend()
    for (auto it = myDeq.begin(); it < myDeq.end(); it++)
    {
        // cat every string by "meow"
        *it += "meow";
    }
    output_std_deque(myDeq, "4. iterator begin -> end cat by meow");
    for (auto it = myDeq.rbegin(); it < myDeq.rend(); it++)
    {
        // cat every element by "baobao"
        *it += "_baobao";
    }
    output_std_deque(myDeq, "5. iterator reverse begin -> rend cat by baobao");    

    // Capacity access: empty(), size(), resize(), max_size(),  shrink_to_fit()
    std::deque<double> myDeq3;
    if (!myDeq.empty())
    {
        myDeq.clear();
        // Creat a new int myDeq
        std::deque<double> myDeq2 = {1.0f, 2.0f, 3.3f, 4.4f, 8.5f, 12.3f};
        cout << "myDeq2.size() = " << myDeq2.size() << endl;
        // This will expand size 6 -> 20 ,with bunch 55.8f behind from 14 - 20
        myDeq2.resize(20, 55.8f);
        output_std_deque(myDeq2, "6. myDeq2.resize1");    
        cout << "myDeq2.size() = " << myDeq2.size() << endl;        
        // this will shrink size from 20 -> 7, but adding no 30.2f anywhere because no need new initialization
        myDeq2.resize(7, 30.2f);
        output_std_deque(myDeq2, "7. myDeq2.resize2");
        cout << "myDeq2.size() = " << myDeq2.size() << endl;

        // copy ctor
        myDeq3 = myDeq2;            
    }
    // Modifiers: clear(), insert(), emplace()/emplace_front()/emplace_back(), erase(), 
    // push_back()/push_front(),  pop_front/pop_back(), swap()

    // We are inserting 6x 3939889 at begin()
    myDeq3.insert(myDeq3.begin(), 6, 3939889.0);
    output_std_deque(myDeq3, "8. myDeq3.insert 1");

    // We are inserting (rbegin - rbegin+3) into the end of myDeq3
    myDeq3.insert(myDeq3.end(), myDeq3.rbegin(), next(myDeq3.rbegin(), 3));
    output_std_deque(myDeq3, "9. myDeq3.insert 2");

    for (auto i=0; i < 3; i++)
    {
        myDeq3.pop_front();
        myDeq3.pop_back();
    }
    output_std_deque(myDeq3, "8. myDeq3 pop_front & pop_back");
    myDeq3.erase(myDeq3.begin(), prev(myDeq3.end(), 3));
    output_std_deque(myDeq3, "9. myDeq3 erase ");
}

/***********************************************
 * STL Forward List:
 * std::forward_list is a container that supports fast insertion and removal of elements from anywhere in the container. 
 * Fast random access is not supported. It is implemented as a singly-linked list. 
 * Compared to std::list this container provides more space efficient storage when bidirectional iteration is not needed.
 * 
 * Note: No size() member function, no rbegin/rend(), no end()
 * Operator == complexity is linear to number of elements
 * Note: iterator cannot compare iterator < list.end() because list does not support end().
 *       can only use for (auto& _ : slist)  to check
 * 
 * Member Functions: Ctor/Dtor, operator =, assign(), get_allocator()
 * Element access: Front()
 * Iterators: before_begin()  // returns an iterator to the element before beginning
 *           begin()
 *           There is no end() // Forward_list maintains no pointer to the end due to O(N) complexity
 * Capacity: empty(), max_size()
 * Modifers: clear(), insert_after()/emplace_after(), erase_after(), push_front()/emplace_front(), pop_front()
 *           resize(), swap()
 * List operations: merge() // merges two sorted lists
 *           splice_after()  // moves elements from another forward_list
 *           remove(), remove_if()  // removes elements satisfying specific criteria
 *           reverse()   // reverse orders 
 *           unique()    // removes consecutive duplicate elements
 *           sort()
 * ********************************************/
template<typename T>
void output_STL_forward_list(std::forward_list<T>& fwdList, string output_tag)
{
    cout << output_tag << " = ";
    // for (auto it = fwdList.begin(); it != fwdList.end(); it++)
    // {
    //     cout << *it;
    // }
    for (auto& element : fwdList)
    {
        cout << element;
    }
    cout << std::endl;
}

template<typename T>
void output_STL_forward_list_space(std::forward_list<T>& fwdList, string output_tag)
{
    cout << output_tag << " = ";
    for (auto& element : fwdList)
    {
        cout << element << " ";
    }
    cout << std::endl;
}

void execute_STL_Forward_List()
{
    std::forward_list<string> fwdList1 = {"q","u","a","l","comm"};
    if (!fwdList1.empty())
    {
        // Qualcomm
        fwdList1.front() = "Q";
        output_STL_forward_list(fwdList1, "fwdList1.front(Q)");

        // pop_front(), push_front()
        fwdList1.pop_front();
        output_STL_forward_list(fwdList1, "fwdList1.pop_front()");        
        fwdList1.push_front("I love Q.....");
        output_STL_forward_list(fwdList1, "fwdList1.push_front(I love Q....)");

        // very huge = 57646075230342387 as this is free memory size 
        cout << "max_size = " << fwdList1.max_size() << endl;;
        fwdList1.clear();
        // max_size still the same
        cout << "after clear max_size() = " << fwdList1.max_size() << endl;
        fwdList1.resize(1000);
        cout << "after re_size(1000) = " << fwdList1.max_size() << endl;

        // assign
        fwdList1.assign({"q","u","a","l","comm"}); // qualcomm
        output_STL_forward_list(fwdList1, "fwdList1.assign(qualcomm)");  

        // erase_after
        fwdList1.erase_after(next(fwdList1.begin(),3));  // qual
        output_STL_forward_list(fwdList1, "fwdList1.erase_after(begin()+3)");

        // insert_after(), Note: MUST USE iterator before_begin() to reach the last element then call insert_after(), end() will point to NULL
        // 3 ways to insert, 
        // a. via  initializer {},
        // b. via iterators first,end from another list
        // c. via count + val

        // a. via initializer:
        fwdList1.insert_after(fwdList1.begin(), {",comm ", "what a ", "lovely ", "company"});
        output_STL_forward_list(fwdList1, "insert 1. fwdList1.insert_after() 1");

        // b. via iterators range
        fwdList1.assign({"q","u","a","l","comm"}); // qualcomm
        std::forward_list<string> fwdList2;
        fwdList2.assign({"stock price = ", "$148.75", " keep going ", "up!"});
        output_STL_forward_list(fwdList2, "fwdList2");
        
        // did all below in order to traverse thru the forward list...
        auto it = fwdList1.before_begin();
        for (auto _ : fwdList1)
        {
            it++;
        }
        // works: fwdList1 + fwdList2
        fwdList1.insert_after(it, fwdList2.begin(), fwdList2.end());
        output_STL_forward_list(fwdList1, "insert 2. fwdList1.insert_after(fwdList2)");

        // c. via count + val
        auto it2 = fwdList2.before_begin();
        std::advance(it2, std::distance(fwdList2.begin(), fwdList2.end()));
        fwdList1.insert_after(it2, 5, " 888");    // insert 5 "888" to the end of the forward list
        output_STL_forward_list(fwdList2, "insert 3. fwdList2 insert_after(it2, 5, 888)");

        // Merge(), splice_after(), remove(), remove_if(), reverse(), unique(), sort()
        // 1. Sort()
        std::forward_list<float> floatFwdList;
        floatFwdList.assign({4.0f, 9.0f, 3.0f, 3.88f, 4.32f, 5.38f, 11.9f, 1.2f});
        output_STL_forward_list(floatFwdList, "before sort ");   // 4.0f, 9.0f, 3.0f, 3.88f, 4.32f, 5.38f, 11.9f, 1.2f
        floatFwdList.sort();
        output_STL_forward_list_space(floatFwdList, "post sort ");   // 1.2 3 3.88 4 4.32 5.38 9 11.9

        // 2. Merge()
        std::forward_list<float> floatFwdList2;
        floatFwdList2.assign({3.5, 2.5f, 9.5f, 8.5f, 12.5f, 6.5f});
        floatFwdList2.sort();    // Both forward lists must sort first before merge
        floatFwdList.merge(floatFwdList2); // merge floatFwdList & floatFwdList2, now floatFwdList2 is empty as all elements being moved
        output_STL_forward_list_space(floatFwdList, "Merge(floatFwdList1, floatFwdList2");
                                // 1.2 2.5 3 3.5 3.88 4 4.32 5.38 6.5 8.5 9 9.5 11.9 12.5

        // 3. reverse()
        floatFwdList.reverse();
        output_STL_forward_list_space(floatFwdList, "reverse(floatFwdList)");
                                // 12.5 11.9 9.5 9 8.5 6.5 5.38 4.32 4 3.88 3.5 3 2.5 1.2
        
        // 4. remove()/remove_if()
        for (auto i = 0; i < 15; i++)
        {
            floatFwdList.remove(static_cast<float>(i) + 0.5);  // Should remove all the 0.5 entries
        }
        output_STL_forward_list_space(floatFwdList, "remove(i+0.5)");   // 11.9 9 5.38 4.32 4 3.88 3 1.2
        // remove all the float values that are even numbers
        floatFwdList.remove_if([](float n){ return static_cast<int>(n) % 2 == 0;});
        output_STL_forward_list_space(floatFwdList, "remove_if(even_num)");   // 11.9 9 5.38 3.88 3 1.2

        // 5. splice_after(), this will insert & move the whole array from list2 into list1 
        output_STL_forward_list_space(floatFwdList, "floatFwdList");    // floatFwdList = 11.9 9 5.38 3.88 3 1.2
        floatFwdList2.assign({40.1f, 50.3f, 65.3f, 23.5f, 72.8f});
        output_STL_forward_list_space(floatFwdList2, "floatFwdList2");  // floatFwdList2 = 40.1 50.3 65.3 23.5 72.8
        floatFwdList.splice_after(floatFwdList.before_begin(), floatFwdList2);
        output_STL_forward_list_space(floatFwdList, "Splice_after(floatFwdList2)");    // 40.1 50.3 65.3 23.5 72.8 11.9 9 5.38 3.88 3 1.2

        // 6. unique(), remove all the contiguous duplicates
        std::forward_list<int> fwdListInt = {1, 2, 2, 2, 3, 3, 3, 4, 5, 4, 4, 6,6, 7, 5, 5, 5, 7, 8, 9, 9, 10, 0, 0, 1};
        fwdListInt.unique();   
        output_STL_forward_list_space(fwdListInt, "fwdListInt.unique()");    // 1 2 3 4 5 4 6 7 5 7 8 9 10 0 1       
    }
}


/****************************************************************
 * STL List:
 * std::list is a container that supports constant time insertion and removal of elements from anywhere in the container. 
 * Fast random access is not supported. It is usually implemented as a doubly-linked list. Compared to std::forward_list this
 *  container provides bidirectional iteration capability while being less space efficient.
 * 
 *  Note: for forward_list and list, both iterators cannot use < it.end(), can only use != end() due to non-seqeuncial 
 *  Member Functions: Ctor/Dtor, operator=, assign(), get_allocator()
 *  Element access:  front(), back() 
 *  Iterators: begin()/end()/rbegin()/rend()
 *  Capacity: empty(), size(), max_size()
 *  Modifers: clear(), insert()/emplace(), erase(), push_back()/push_front(), pop_back()/pop_front(), emplace_back()/emplace_front(),
 *            resize(), swap()
 *  Operations: merge(), splice(), remove()/remove_if(), reverse(), unique(), sort()
 * 
 * ***************************************************************/
template<typename T>
void output_std_list(std::list<T>& inputList, string output_tag)
{
    cout << output_tag << " = ";
    for (auto it = inputList.begin(); it != inputList.end(); it++)
    {
        cout << *it << " ";
    }
    cout << std::endl;
}

void execute_STL_List()
{
    std::list<string> fruitList = {"Apple"};
    fruitList.assign({"Orange", "Apple", "Watermelon", "Banana", "Kiwi"});
    output_std_list(fruitList, "fruitList");
    cout << "size = " << fruitList.size() << " max_size = " << fruitList.max_size() << endl;

    fruitList.front() = "Big_Orange";
    fruitList.back()  = "Small_Kiwi";
    output_std_list(fruitList, "fruitList");

    std::list<double> fruitPriceList;
    if (fruitPriceList.empty())
    {
        auto it = fruitList.begin();
        for (auto i = 0; i < fruitList.size(); i++, advance(it, 1))
        {
            double price = 0;
            if (*it == "Big_Orange")
                price = 30.5f;       // orange price = 30.5
            else if (*it == "Apple")  // Apple price = 12.5
                price = 12.5f;
            else if (*it == "Watermelon")
                price = 87.5f;
            else if (*it == "Banana")
                price = 56.8f;
            else if (*it == "Small_Kiwi")
                price = 99.35f;
            
            cout << "i = " << i << " = " << price << endl;
            fruitPriceList.push_back(price);
        }
    }
    output_std_list(fruitPriceList, "fruitPriceList");

//   Modifers: clear(), insert()/emplace(), erase(), push_back()/push_front(), pop_back()/pop_front(), 
//             emplace_back()/emplace_front(), resize(), swap()
    list<double> tempFruitPriceList = fruitPriceList;
    fruitPriceList.clear();
    output_std_list(fruitPriceList, "fruitPriceList.clear()");
    fruitPriceList = tempFruitPriceList;

    // insert(), 3 ways to insert.
    tempFruitPriceList.insert(tempFruitPriceList.end(), 5, 10000.0); // insert 5 x 10000 at end of list
    output_std_list(tempFruitPriceList, "tempFruitPriceList.insert() 1");
    tempFruitPriceList.insert(tempFruitPriceList.begin(), {8888.8, 8888.8, 8888.8, 8888.8, 8888.8}); // insert 5 x 8888.8 at begin of list
    output_std_list(tempFruitPriceList, "tempFruitPriceList.insert() 2");
    tempFruitPriceList.insert(tempFruitPriceList.end(), fruitPriceList.begin(), prev(fruitPriceList.end(), 3));  // insert fruitPriceList into begin
    output_std_list(tempFruitPriceList, "tempFruitPriceList.insert() 3");

    // erase()
    tempFruitPriceList.erase(tempFruitPriceList.begin(), next(tempFruitPriceList.begin(), 5));
    tempFruitPriceList.erase(prev(tempFruitPriceList.end(), 7), tempFruitPriceList.end());
    output_std_list(tempFruitPriceList, "tempFruitPriceList.erase() ");

    // pop_back() & pop_front)
    while (tempFruitPriceList.size() != 0)
    {
        tempFruitPriceList.pop_front();
        output_std_list(tempFruitPriceList, "tempFruitPriceList.pop_front() ");

        if (!tempFruitPriceList.empty())
        {
            tempFruitPriceList.pop_back();
            output_std_list(tempFruitPriceList, "tempFruitPriceList.pop_back() ");
        }
    }

    // Swap()
    tempFruitPriceList.swap(fruitPriceList);
    output_std_list(tempFruitPriceList, "tempFruitPriceList.swap() ");
    output_std_list(fruitPriceList, "fruitPriceList.swap() ");
    
    //   Operations: merge(), splice(), remove()/remove_if(), reverse(), unique(), sort()
    tempFruitPriceList.swap(fruitPriceList);
    fruitPriceList.sort();
    output_std_list(fruitPriceList, "fruitPriceList.sort() ");
    fruitPriceList.reverse();
    output_std_list(fruitPriceList, "fruitPriceList.reverse() 1 ");
    fruitPriceList.reverse();
    output_std_list(fruitPriceList, "fruitPriceList.reverse() 2 "); 
    list<double> fruitPriceList2 = {39.0, 39.5, 103.3, 68.9f, 2.3f, 78.5f};
    fruitPriceList2.sort();

    fruitPriceList.merge(fruitPriceList2);
    output_std_list(fruitPriceList, "fruitPriceList.merge(fruitPriceList2) ");

    // remove_if()
    fruitPriceList.remove_if([](double input){ return input <= 50;});
    output_std_list(fruitPriceList, "fruitPriceList.remove_if(input <= 50) ");  
}

/*********************************************************************
 * STL Queue:
 * The std::queue class is a container adapter of deque<T> that gives FIFO queue
 * The class template adcts as a wrapper the the underlying container
 * Allows push back and pop front
 * 
 * Member functions: CTOR, DTOR, operatior=
 *  1) Copy assignment operator. Replaces the contents with a copy of the contents of other. Effectively calls c = other.c;. 
 *  2) Move assignment operator. Replaces the contents with those of other using move semantics. Effectively calls c = std::move(other.c);
 * 
 * Member object: Container c = std::deque<T> // (the underlying container)(Protected member object)
 * Element access: front(), back()
 * Capacity: empty(), size()
 * Modifiers: push()/emplace()  // at the end
 *            pop()   // the front
 *            swap()
 * 
 * Note: Problem with queue is that it has no iterator, clear() or initializing list. Make it very hard to use.
 *       It has only limited functions, though underlying deque<T> is very powerful. It is also very hard to print values as you will
 *      need to pass a copy then pop() one by one to print. This is kind of stupid.
 * *******************************************************************/
template<typename T>
void output_std_queue(std::queue<T> inputQ, string output_tag)
{
    cout << output_tag << " = ";
    while (!inputQ.empty())
    {
        cout << inputQ.front() << " ";
        inputQ.pop();  // pop the front
    }
    cout << endl;
}

void execute_STL_Queue()
{
    std::queue<string> queue1;
    queue1.push("abc");
    queue1.push("def");
    queue1.push("xyz");
    
    std::queue<string> queue2 = queue1;
    cout << "queue.back() = " << queue1.back() << " queue.front() = " << queue1.front() << endl;  // queue1 = xyz abc
    if (!queue1.empty())
    {
        cout << "queue.size() = " << queue1.size() << endl;  // 3
        queue1.pop();
        queue1.pop();
        cout << "queue.size() after 2 pops = " << queue1.size() << " queue.front() = " \
            << queue1.front() << " queue.back() = " << queue1.back() << endl;;   // 1, xyz, xyz
    }

    output_std_queue(queue1, "queue1");   // xyz
    output_std_queue(queue2, "queue2");   // abc def xyz
    queue2.swap(queue1);
    output_std_queue(queue1, "queue1 swapped");   // abc def xyz
    output_std_queue(queue2, "queue2 swapped");   // xyz
}

/************************************************************************
 * STL Priority Queue:
 * A priority queue is a container adapter of std::vector<T> that provides constant time look-up of the largest element,
 * at the expense of lgarithmic insertion and extraction.
 * A priority queue can be similar to managing a heap, with the benefit of not being able to accidentally invalidate the heap.
 * 
 * Member objects:
 * Container c - std::vector and std:deque satisfies. Need front(), push_back(), pop_back() 
 * Compare comp - comparison function object
 * 
 * Member functions: CTOR/DTOR, operator=
 * Element access: top()  // give top element
 * Capacity: empty()/size()
 * Modifiers: push(), emplace(), pop(), swap()
 * 
 * Note: priority_queue<T> will always put the comparison win result at top. We can specify different comparison win result. 
 * ***********************************************************************/
template<typename T>
void output_STL_priority_queue(std::priority_queue<T> input_queue, string output_tag)
{
    cout << output_tag << " = ";
    while (!input_queue.empty())
    {
        cout << input_queue.top() << " ";
        input_queue.pop();
    }
    cout << endl;
}

void execute_STL_Priority_Queue()
{
    std::priority_queue<int> p_queue1;
    p_queue1.push(-5);
    p_queue1.push(15);
    p_queue1.push(7);
    p_queue1.push(-8);
    p_queue1.push(-23);
    p_queue1.push(87);
    p_queue1.push(0);

    std::priority_queue<int> p_queue2 = p_queue1;

    cout << "p_queue1.top() = " <<  p_queue1.top() << " p_queue1.size() = " << p_queue1.size() << endl;
    output_STL_priority_queue(p_queue1, "p_queue1 print");

    // <value_type, container<value_type>, comparison_object>
    std::priority_queue<float, std::vector<float>, std::less<float>> p_queue3;
    p_queue3.push(-3.83);
    p_queue3.push(-2.93);
    p_queue3.push(-1.73);
    p_queue3.push(-10.23);
    p_queue3.push(8.83);
    p_queue3.push(3.03);                  

    output_STL_priority_queue(p_queue3, "p_queue3");  
}