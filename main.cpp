#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <vector>
#include <array>
#include <functional>
#include <algorithm>
#include <thread>
#include <unistd.h>
#include <iterator>
#include<deque>
#include<queue>
#include <stack>
#include <list>
#include<map>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#if LINUX == 2
#define MAX 1
#else 
#define MAX 2
#endif

//单链表
struct ListNode
{
	int data;
	ListNode* next;//结构体指针
};

//打印链表
void Listprintf(ListNode* phead)
{
    ListNode* ptail = phead;
    while(ptail != nullptr) 
    {
        std::cout << ptail->data << "->";
        ptail = ptail->next;
    };
    std::cout << "NULL" <<std::endl;
}

//尾插
void Listpushback(ListNode** pphead, int value)//注意指针的指针
{
    if(*pphead == NULL) //空链表要创新头，后面tail->next会访问空指针
    {
        *pphead = new ListNode{value,nullptr};    
    }else
    {
        ListNode* tail = *pphead;
        while(tail->next != NULL) //找尾
        {
            tail=tail->next;
        }
        tail->next=new ListNode{value,nullptr};//尾后放置新节点
    }
}

//头插
void Listpushfront(ListNode** pphead,int value)
{
    ListNode* newnode = new ListNode{value,nullptr};//创新节点
    newnode->next=*pphead;//新节点的next指针指向头节点
    *pphead=newnode;//头节点重新指向新节点
}

//尾删
void Listpopback(ListNode** pphead)
{
    if(*pphead == nullptr) //empty list要判空，否则下面tail->next会访问空指针
    {
        return;
    }

    if((*pphead)->next == nullptr) //单节点情况要判空，下面会访问prev->next造成空指针
    {
        delete(*pphead);
        *pphead=nullptr;
    }else
    {
        ListNode* tail = *pphead;
        ListNode* prev = nullptr;
        
        while (tail->next != NULL) //寻找尾节点
        {
            prev = tail;
            tail=tail->next;
        }
        delete tail;  //删除尾节点
        tail = nullptr; //尾节点指向空
        prev->next=nullptr;//前一个节点的next指针置空
    }
}

//头删
void Listpopfront(ListNode** pphead)
{
    if(*pphead == nullptr) //empty not needed delete
    {
        return;
    }

    ListNode* tail = *pphead;
    tail = tail->next;//尾部后移一个节点
    delete(*pphead);//删除头节点
    *pphead=tail;//头节点重新指向后移节点
}

//按值查找元素，返回值是地址
ListNode* ListFind(ListNode** pphead,int value)
{
    ListNode* tail = *pphead;
    while((tail != nullptr))  //从头开始找
    {
        if((tail->data == value)) //匹配数值
            return tail;     
        else
            tail=tail->next;      //匹配不上，继续往后找
    }
    return nullptr;
}

//指定位置插入元素，在pos插入
bool ListInsert(ListNode **pphead,int pos,int value)
{
    if(pos < 0)
    {
        std::cout << "Invalid position"<<std::endl;
        return false; 
    }
    ListNode *newnode = new ListNode{value,*pphead};
    if(*pphead == nullptr)
    {
        *pphead = newnode;
    }else
    {
        ListNode *tail = *pphead;
        while(pos--)          //往后移动pos位置
        {
            if(tail == nullptr || tail->next == nullptr)
            {
                std::cout << "error pos" << pos <<std::endl;
                return false; 
            }else
            {
                tail=tail->next;
            }
            
        }
        newnode->next = tail->next; //新节点next指针指向当前的下一个位置
        tail->next=newnode; //当前位置next指针指向新节点
        return true;
    }
}

//释放链表
void ListRelease(ListNode **phead)
{
    ListNode *tail = *phead;
    while(tail != nullptr)
    {
        tail = tail->next;
        delete *phead;
        *phead = tail;
    }

}

//反转链表 leedcode206
void ListReserve(ListNode **phead)
{
    ListNode *prev = nullptr; //表示当前节点的前一个节点
    ListNode *cur = *phead;  //表示当前节点
    ListNode *tail = nullptr;
    while(cur != nullptr)    //迭代处理
    {
        tail = cur->next; //暂存下一个节点
        cur->next = prev;  //当前节点指向前一个节点
        prev = cur;        //前节点后移
        cur = tail;        //当前节点移至下一个节点
    }
    *phead = prev;         //更新原链表指向
}

//寻找中间节点 leetcode876 遍历两次
ListNode* ListMiddleNode(ListNode **phead)
{
        int nodenum = 0u;
        int middle_pos = 0u;
        ListNode* cur = *phead;
        while(cur != nullptr)
        {
            cur = cur->next;
            nodenum++;
        }

        cur = *phead;
        while(middle_pos < nodenum/2)
        {
            middle_pos++;
            cur=cur->next;
        }
        return cur;
}

//寻找中间节点 leetcode876 快慢指针
ListNode* ListMiddleNode_ptr(ListNode **phead)
{
        ListNode* slow = *phead;
        ListNode* quick = *phead;
        while(quick != nullptr && quick->next != nullptr)
        {
            slow = slow->next;
            quick = quick->next->next;
        }
        return slow;
}

//反转链表2 leetcode 92
ListNode* ListResver(ListNode** phead,int left,int right)
{
    ListNode* node = new ListNode{0,nullptr}; //create new node or pos 1 can not swap when left is 1
    node->next = *phead;
    ListNode* prev = node;
    for(int i = 0u;i<left-1;i++)
    {
        prev=prev->next;
    }
    
    ListNode* cur = prev->next;
    ListNode* next = cur->next;

    for(int i = 0;i <  right - left;i++)
    {
        next = cur->next;
        cur->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }
    return node->next;
}

//奇偶链表
ListNode* oddEvenList(ListNode** phead)
{
    if(*phead == nullptr) 
    {
        return nullptr;
    }
    ListNode* odd = *phead;
    ListNode* oven = odd->next;
    ListNode* oven_head = (*phead)->next;
    while(odd->next != NULL && oven->next != NULL)
    {
        odd->next = oven->next;//偶节点的下一个节点必然是奇节点
        odd = odd->next;
        oven->next = odd->next;
        oven = oven->next;
    }

    odd->next = oven_head;
    return *phead;
}

//2 两数相加
ListNode* ListAdd(ListNode** phead1,ListNode** phead2)
{
    ListNode* p1=*phead1;
    ListNode* p2=*phead2;
    ListNode* listadd = new ListNode{0,nullptr};
    ListNode* prev = listadd;
    int numadd = 0;
    int numresult = 0;//个位
    int addresult = 0;//进位
    int p1data;
    int p2data;
    
    while(p1 != nullptr || p2 != nullptr)
    {
        
        p1data = (p1 == nullptr) ? 0 : p1->data;
        p2data = (p2 == nullptr) ? 0 : p2->data;
        numadd = p1data + p2data + addresult;   
        numresult = numadd%10;
        addresult = ((numadd)/10)?1 : 0;
        if(p1 != NULL)
        {
            p1=p1->next;
        }  
            
        if(p2 != NULL) 
        {
            p2=p2->next;
        }     
        
        listadd->next = new ListNode{numresult,nullptr};
        listadd = listadd->next;
        
    }
    if(addresult == 1)
    {
        listadd->next = new ListNode{1,nullptr};
    }

    return listadd=prev->next;
}

//21:合并两个升序列表
ListNode* ListMerge(ListNode** phead1, ListNode** phead2)
{
    if(*phead1 == nullptr)
    {
        return *phead2;
    }

    if(*phead2 == nullptr)
    {
        return *phead1;
    }

    if((*phead1)->data <= (*phead2)->data)
    {
        (*phead1)->next = ListMerge(&((*phead1)->next),&(*phead2));
        return *phead1;
    }else
    {
        (*phead2)->next = ListMerge(&(*phead1),&((*phead2)->next));
        return *phead2;
    }
} 


typedef struct data{
        char m:3;
        char n:5;
        short s;
        union{
            int a;
            char b;
        };
        int h;
}__attribute__((packed)) data_t;

void sizeof_test()
{
    data_t data;
    data.m= 1;
    // memset(&data, 0, sizeof(data));
    // printf("m[%d] m[%n] s[%d] a[%d] b[%d] h[%d] size[%d]",&data.m,&data.n,&data.s,&data.a,&data.b,&data.h,sizeof(data));
    int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	memcpy(a + 3, a, 5);
	for (int i = 0; i<10; i++){
		printf("%d ", a[i]);
	}
}

//字符串 反转字符串
 void reverseString(std::vector<char>& s)
{
        //交换头尾，迭代完成
        int size = s.size();
        for(int left = 0u,right = size-1;left < right;left++,right--)
        {
            std::swap(s[left],s[right]);
        }
}


//字符串 反转字符串 541
 std::string reverseStringII(std::string s,int k)
{
    for(int i=0;i< s.length();i+= 2*k)
    {
        if(i+k <= s.length())
        {
            reverse(s.begin() + i,s.begin() + i +k);
            continue;
        }
        reverse(s.begin() + i , s.begin() + s.length());
    }    
    return s;
}

//剑指 Offer 05. 替换空格
std::string replace_place(std::string s)
{
    int count = 0;
    int len = s.size();
    for(auto it = s.begin(); it != s.end();it++)
    {
        if((*it) == ' ')
        {
            count++;
        }
    }

    s.resize(s.size() + 2*count);
    for(int i = len -1,j = s.size() -1;i<j;i--,j--)
    {
        if(s[i] != ' ')
        {
            s[j] = s[i];
        }else
        {
            s[j] = '0';
            s[j-1] =  '2';
            s[j-2] = '%';
            j -= 2;
        }
    }
    return s;
}

//字符串 LeetCode3: 无重复字符的最长子串
int lengthOfLongestSubstring(std::string s)
{
    int start =0u;
    int end = 0u;
    int maxlength = 0u;
    int length=0u;
    while(end<s.length())
    {
        for(int index = start;index < end;index++)
        {
            if(s[index] == s[end])
            {
                start = index + 1;
                length = end - start;
                break;
            }
        }

        length ++;
        end++;
        maxlength = std::max(maxlength,length);
    }
    return maxlength;
}

// [409] 最长回文串
int longestPalindrome(std::string s)
{
    std::unordered_map<char,int> palindrome;
    for(char c : s)//统计字符出现的个数，并放入hash表
    {
        palindrome[c]++;
    }
    int odd = 0u;
    int res = 0u;
    for(auto it :  palindrome)
    {
        res += it.second - (it.second % 2);//减去余数1,为偶数个数，5-1=4
        if(it.second % 2 == 1)//如果是奇数，odd置1,比如1,3
            odd =1;
    }
    return (res+odd);
}

//49 字母异位词分组
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) 
{
    std::unordered_map<std::string, std::vector<std::string>> group;
    for(auto str : strs)    //将排序后的字符串作为键，排序前的字符串作为值
    {
        std::string tmpstring = str;
        std::sort(str.begin(), str.end());
        group[str].push_back(tmpstring);
    }

    std::vector<std::vector<std::string>> res;//将值组成vector输出
    for(auto map : group)
    {
        res.push_back(map.second);
    }
    return res;
}


void string_test()
{
    std::vector<char> s;
    s.push_back(31);
    s.push_back(32);
    s.push_back(33);
    
    std::vector<char> &a = s;
    reverseString(a);

    std::string str = "abcdef";
    str = reverseStringII(str,2);

    str = "1 3 5";
    std::string str_1 = replace_place(str);


    str = "bbbbb";
    int maxlen = lengthOfLongestSubstring(str);

    str = "aaaaaccc";
    int maxlong = longestPalindrome(str);

    std::vector<std::string> test_string = {"eat","tea","tan","ate","nat","bat"};
    groupAnagrams(test_string);

}



void list_test()
{
	ListNode* phead = NULL;
    ListNode* phead2 = NULL;
    // for(int i = 1; i < 5 ;i++)
    //     Listpushback(&phead,i);

    // for(int i = 0; i < 3 ;i++)
    //     Listpushback(&phead2,i;
    Listpushback(&phead,1);
    Listpushback(&phead,5);
    Listpushback(&phead,7);

    Listpushback(&phead2,1);
    Listpushback(&phead2,3);
    Listpushback(&phead2,9);

    // Listpushfront(&phead,0);
    // ListInsert(&phead,0,5);
    // Listpopback(&phead);
    // Listpopfront(&phead);
    // ListNode* findnode = ListFind(&phead,2);
    // if(findnode != nullptr)
    //     std::cout << "Find node " << std::endl;
    // else
    //     std::cout << "No node found" << std::endl;
    Listprintf(phead);
    Listprintf(phead2);
    Listprintf(ListMerge(&phead,&phead2));
    // Listprintf(ListResver(&phead,2,4));
    // Listprintf(oddEvenList(&phead));
    // ListReserve(&phead);
    // std::cout << "Miidle value is[" << ListMiddleNode_ptr(&phead)->data << "]" << std::endl;
    // Listprintf(phead);
    // ListRelease(&phead);
    // Listprintf(phead);
}

//hash 1两数之和
std::vector<int> twoSum(std::vector<int>& nums, int target) 
{
    //哈希表
    std::unordered_map<int,int> map;
    for(int i = 0; i < nums.size();i++)
    {
        auto it = map.find(target - nums[i]);
        if(it != map.end())
        {
            return {i,it->second};
        }
        map[nums[i]] = i;
    }
    return {};
}

//[128] 最长连续序列
int longestConsecutive(std::vector<int>& nums) 
{
    //hash set去重
    std::unordered_set<int> set;
    for(auto i : nums)
    {
        set.insert(i);
    }

    int longest  = 0u;
    int current = 0u;
    for(int i : set)
    {
        if(!set.count(i-1))//如果-1的数在，那肯定不是起点，跳过
        {
            current = 1u;
            while(set.count(i+1)) //+1的数在不在？在找到连续，继续找
            {
                current++;
                i++;
            }
        }
        longest = std::max(current, longest);
    }
    std::cout << "longest " << longest << std::endl;
}

//[350] 两个数组的交集 II
std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
{
    //比较两个数组大小，小的作为hash表，统计出现次数，减少轮询次数
    if(nums1.size() > nums2.size())
    {
        return intersect(nums2,nums1);
    }
    std::vector<int> result;
    std::unordered_map<int,int> map;
    //统计各个数的出现次数
    for(int num : nums1)
    {
        map[num]++;
    }
    //如果数组2中的数在数组1中的键找到，map中的次数-1,并将2数组该数放入结果数组
    for(int num : nums2)
    {
        if(map[num])
        {
            map[num]--;
            result.push_back(num);
        }
        //如果已经清零，则删掉map中的键，减少轮询次数
        if(map[num] == 0u)
        {
            map.erase(num);
        }
    }
    return result;
}

void hash_test()
{
    std::vector<int> raw;
    raw.push_back(2);
    raw.push_back(7);
    raw.push_back(11);
    raw.push_back(15);
    std::vector<int> res ;
    res = twoSum(raw,17);

    std::vector<int> raw2;
    raw2.push_back(100);
    raw2.push_back(4);
    raw2.push_back(200);
    raw2.push_back(1);
    raw2.push_back(3);
    raw2.push_back(2);
    raw2.push_back(1);
    int result;
    result = longestConsecutive(raw2);

    std::vector<int> v1;
    std::vector<int> v2;
    v1.push_back(4);
    v1.push_back(4);
    v1.push_back(2);

    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(4);

    std::vector<int> res1;
    res1 = intersect(v1,v2);
}

int binarySearch(std::vector<int>& v1,int ans)
{
    int left = 0u;
    int right = v1.size()-1;
    int mid = 0u;
    while(left <= right) //=的价值在于目标值在头尾的情况，不加会找不到，应为此时left==right
    {
        mid = (left + right)/2;
        if(v1[mid] < ans)
        {
            left = mid+1;
        }else if(v1[mid] > ans)
        {
            right = mid-1;
        }else
        {
            return mid;
        }
    }
     return -1;
}

//
int binarySearch_better(std::vector<int>& v1,int ans,bool lower)
{
    int left = 0u;
    int right = v1.size()-1;
    int mid = 0u;
    int res = -1;
    while(left <= right) //=的价值在于目标值在头尾的情况，不加会找不到，应为此时left==right
    {
        mid = (left + right)/2;
        if(v1[mid] < ans)
        {
            left = mid+1;
        }else if(v1[mid] > ans)
        {
            right = mid-1;
        }else
        {
            res = mid; //找到目标，如果获取左边第一个，改变右区间，如果获取第二个，改变左区间
            if(lower)
            {
                right = mid-1;
            }else
            {
                left = mid+1;
            }
        }
    }
     return res;
}

//leetcode 34 在排序数组中查找元素的第一个和最后一个位置
std::vector<int> searchRange(std::vector<int>& nums, int target) 
{
    std::vector<int> result;
    result.push_back(binarySearch_better(nums,target,true));
    result.push_back(binarySearch_better(nums,target,false));
    return result;
}

//leetcode[240] 搜索二维矩阵 II
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) 
{
    bool res;
    for(const auto& i : matrix)
    {
        res = std::binary_search(i.begin(), i.end(),target);
        if(res == true)
        {
            return res;
        }
    }
    return res;
}

void binarysearch_test()
{
    std::vector<int> test{5,7,7,8,8,10};
    int target = 8;
    // int res = binarySearch(test, target);
    // std::cout << "binarysearch result: " << res << std::endl;
    // res = binarySearch_better(test,target,true);
    // std::cout << "binarySearch_better result: " << res << std::endl;
    // res = binarySearch_better(test,target,false);
    // std::cout << "binarySearch_better result: " << res << std::endl;

    // std::vector<int> result;
    // result= searchRange(test,target);
    // std::cout << "binarySearch_better result: " << std::endl;

    std::vector<std::vector<int>> matrix;
    matrix.push_back({1,2,3,4});
    matrix.push_back({5,6,7,8});
    matrix.push_back({9,10,11,12});
    matrix.push_back({13,14,15,16});

    bool res = searchMatrix(matrix,16);
    std::cout << "searchMatrix result: " << res << std::endl;
}

#define GET_STRUCT_ADDRESS(struct_m) &(struct_m)
int main(int argc, char **argv)
{
    return 0;
}
