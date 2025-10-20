#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;


#include "List.hpp"

TEST(test_empty_cases) {
    List<int> l;
    ASSERT_TRUE(l.empty());
    l.push_back(1);
    ASSERT_TRUE(!l.empty());
    l.pop_back();
    ASSERT_TRUE(l.empty());
    l.push_front(5);
    ASSERT_TRUE(!l.empty());
    l.pop_front();
    ASSERT_TRUE(l.empty());
    l.push_back(2);
    l.clear();
    ASSERT_TRUE(l.empty());
    l.push_back(3);
    l.pop_front();
    ASSERT_TRUE(l.empty());
    l.push_front(4);
    l.pop_back();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(test_size_cases) {
    List<int> l;
    ASSERT_EQUAL(l.size(), 0);
    l.push_back(1);
    ASSERT_EQUAL(l.size(), 1);
    l.push_back(2);
    ASSERT_EQUAL(l.size(), 2);
    l.pop_front();
    ASSERT_EQUAL(l.size(), 1);
    l.pop_back();
    ASSERT_EQUAL(l.size(), 0);
    l.push_front(3);
    l.push_front(4);
    ASSERT_EQUAL(l.size(), 2);
    l.clear();
    ASSERT_EQUAL(l.size(), 0);
    l.push_back(5);
    l.pop_back();
    ASSERT_EQUAL(l.size(), 0);
    l.push_back(6);
    l.push_back(7);
    ASSERT_EQUAL(l.size(), 2);
}

TEST(test_front_cases) {
    List<int> l;
    l.push_back(10);
    ASSERT_EQUAL(l.front(), 10);
    l.push_front(20);
    ASSERT_EQUAL(l.front(), 20);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 10);
    l.clear();
    l.push_front(30);
    ASSERT_EQUAL(l.front(), 30);
    l.push_front(40);
    ASSERT_EQUAL(l.front(), 40);
    l.push_back(50);
    ASSERT_EQUAL(l.front(), 40);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 30);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 50);
    l.pop_front();
    l.push_back(60);
    ASSERT_EQUAL(l.front(), 60);
}

TEST(test_back_cases) {
    List<int> l;
    l.push_back(1);
    ASSERT_EQUAL(l.back(), 1);
    l.push_back(2);
    ASSERT_EQUAL(l.back(), 2);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 1);
    l.push_front(0);
    ASSERT_EQUAL(l.back(), 1);
    l.pop_front();
    ASSERT_EQUAL(l.back(), 1);
    l.pop_back();
    l.push_front(3);
    ASSERT_EQUAL(l.back(), 3);
    l.push_back(4);
    ASSERT_EQUAL(l.back(), 4);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 3);
    l.clear();
    l.push_back(5);
    ASSERT_EQUAL(l.back(), 5);
}

TEST(test_push_front_cases) {
    List<int> l;
    l.push_front(1);
    ASSERT_EQUAL(l.front(), 1);
    l.push_front(2);
    ASSERT_EQUAL(l.front(), 2);
    l.push_front(3);
    ASSERT_EQUAL(l.front(), 3);
    ASSERT_EQUAL(l.back(), 1);
    ASSERT_EQUAL(l.size(), 3);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 2);
    l.clear();
    l.push_front(4);
    ASSERT_EQUAL(l.front(), 4);
    l.push_back(5);
    l.push_front(6);
    ASSERT_EQUAL(l.front(), 6);
    ASSERT_EQUAL(l.back(), 5);
}

TEST(test_push_back_cases) {
    List<int> l;
    l.push_back(1);
    ASSERT_EQUAL(l.back(), 1);
    l.push_back(2);
    ASSERT_EQUAL(l.back(), 2);
    l.push_back(3);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.size(), 3);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 2);
    l.clear();
    l.push_back(4);
    ASSERT_EQUAL(l.back(), 4);
    l.push_front(5);
    l.push_back(6);
    ASSERT_EQUAL(l.back(), 6);
    ASSERT_EQUAL(l.front(), 5);
}

TEST(test_pop_front_cases) {
    List<int> l;
    l.push_back(1);
    l.pop_front();
    ASSERT_TRUE(l.empty());
    l.push_back(2);
    l.push_back(3);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 3);
    l.clear();
    l.push_front(4);
    l.push_back(5);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 5);
    l.pop_front();
    ASSERT_TRUE(l.empty());
    l.push_front(6);
    ASSERT_EQUAL(l.front(), 6);
    l.pop_front();
    ASSERT_TRUE(l.empty());
    l.push_back(7);
    ASSERT_EQUAL(l.front(), 7);
}

TEST(test_pop_back_cases) {
    List<int> l;
    l.push_back(1);
    l.pop_back();
    ASSERT_TRUE(l.empty());
    l.push_back(2);
    l.push_back(3);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 2);
    l.clear();
    l.push_front(4);
    l.push_back(5);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 4);
    l.pop_back();
    ASSERT_TRUE(l.empty());
    l.push_back(6);
    ASSERT_EQUAL(l.back(), 6);
    l.pop_back();
    ASSERT_TRUE(l.empty());
    l.push_front(7);
    ASSERT_EQUAL(l.back(), 7);
}

TEST(test_clear_cases) {
    List<int> l;
    l.clear();
    ASSERT_TRUE(l.empty());
    l.push_back(1);
    l.clear();
    ASSERT_TRUE(l.empty());
    l.push_back(2);
    l.push_back(3);
    l.clear();
    ASSERT_TRUE(l.empty());
    l.push_front(4);
    l.push_back(5);
    l.clear();
    ASSERT_TRUE(l.empty());
    l.push_back(6);
    l.clear();
    ASSERT_EQUAL(l.size(), 0);
    l.push_front(7);
    ASSERT_EQUAL(l.front(), 7);
    l.clear();
    ASSERT_TRUE(l.empty());
    ASSERT_TRUE(l.begin() == l.end());
}

TEST(test_insert_cases) {
    List<int> l;
    auto it = l.begin();
    l.insert(it, 1);
    ASSERT_EQUAL(*l.begin(), 1);
    it = l.begin();
    l.insert(it, 0);
    ASSERT_EQUAL(*l.begin(), 0);
    l.push_back(2);
    it = l.begin();
    ++it;
    l.insert(it, 99);
    it = l.begin();
    ASSERT_EQUAL(*it++, 0);
    ASSERT_EQUAL(*it++, 99);
    ASSERT_EQUAL(*it++, 1);
    ASSERT_EQUAL(*it++, 2);
    ASSERT_EQUAL(l.size(), 4);
    l.clear();
    it = l.begin();
    l.insert(it, 5);
    ASSERT_EQUAL(*l.begin(), 5);
    ASSERT_EQUAL(l.size(), 1);
}

TEST(test_erase_cases) {
    List<int> l;
    l.push_back(1);
    auto it = l.begin();
    l.erase(it);
    ASSERT_TRUE(l.empty());
    l.push_back(2);
    l.push_back(3);
    it = l.begin();
    ++it;
    l.erase(it);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.back(), 2);
    l.push_back(4);
    it = l.begin();
    ++it;
    l.erase(it);
    ASSERT_EQUAL(*l.begin(), 2);
    ASSERT_EQUAL(l.back(), 2);
    l.clear();
    l.push_back(5);
    l.erase(l.begin());
    ASSERT_TRUE(l.empty());
    l.push_front(6);
    l.push_back(7);
    it = l.begin();
    l.erase(it);
    ASSERT_EQUAL(l.front(), 7);
    ASSERT_EQUAL(l.back(), 7);
}

TEST(test_iterator_all) {
    List<int> list;

    List<int>::Iterator default_it1, default_it2;
    ASSERT_TRUE(default_it1 == default_it2);

    list.push_back(5);
    auto it = list.begin();
    ASSERT_EQUAL(*it, 5);

    list.push_back(10);
    list.push_back(15);
    it = list.begin();
    ASSERT_EQUAL(*it, 5);
    ++it;
    ASSERT_EQUAL(*it, 10);
    it++;
    ASSERT_EQUAL(*it, 15);

    auto post = list.begin();
    auto old = post++;
    ASSERT_EQUAL(*old, 5);
    ASSERT_EQUAL(*post, 10);

    it = list.begin();
    ++it; // now at 10
    ASSERT_EQUAL(*--it, 5);

    it = list.end();
    auto before = it--;
    ASSERT_TRUE(before == list.end());
    ASSERT_EQUAL(*it, 15);

    auto a = list.begin();
    auto b = list.begin();
    ASSERT_TRUE(a == b);
    ++b;
    ASSERT_TRUE(a != b);

    List<int>::Iterator def;
    ASSERT_TRUE(def != a);

    list.clear();
    for (int i = 0; i < 4; ++i) {
        list.push_back(i);
    }

    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ASSERT_EQUAL(*it, i++);
    }

    i = list.size();
    auto it2 = list.end();
    while (it2 != list.begin()) {
        --it2;
        --i;
        ASSERT_EQUAL(*it2, i);
    }
}

TEST(test_empty_list_properties) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_push_pop_single_element) {
    List<int> list;
    list.push_back(42);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 42);
    ASSERT_EQUAL(list.back(), 42);
    list.pop_front();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_push_front_pop_back_order) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 1);
    list.pop_back();
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 2);
    ASSERT_EQUAL(list.size(), 1);
}

TEST(test_pop_front_until_empty) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQUAL(list.front(), i);
        list.pop_front();
    }
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_iterator_postfix_vs_prefix) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.begin();
    ASSERT_EQUAL(*it++, 10);
    ASSERT_EQUAL(*it, 20);
    --it;
    ASSERT_EQUAL(*++it, 20);
}

TEST(test_insert_begin_and_erase) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);
    auto it = list.begin();
    list.insert(it, 1);
    it = list.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
    it = list.begin();
    ++it;
    list.erase(it);
    it = list.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 3);
}

TEST(test_insert_at_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it = list.end();
    list.insert(it, 3);
    auto iter = list.begin();
    ASSERT_EQUAL(*iter++, 1);
    ASSERT_EQUAL(*iter++, 2);
    ASSERT_EQUAL(*iter++, 3);
    ASSERT_TRUE(iter == list.end());
}

TEST(test_erase_all_elements_one_by_one) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    auto it = list.begin();
    while (it != list.end()) {
        it = list.erase(it);
    }
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_copy_then_modify_original) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    List<int> list2(list1);
    list1.pop_back();
    ASSERT_EQUAL(list1.size(), 2);
    ASSERT_EQUAL(list2.size(), 3);
    auto it2 = list2.begin();
    ASSERT_EQUAL(*it2++, 1);
    ASSERT_EQUAL(*it2++, 2);
    ASSERT_EQUAL(*it2++, 3);
}

TEST(test_assign_self_assignment) {
    List<int> list;
    list.push_back(99);
    list = list;
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 99);
    ASSERT_EQUAL(list.back(), 99);
}

TEST(test_compare_default_iterators) {
    List<int>::Iterator it1, it2;
    ASSERT_TRUE(it1 == it2);
}

TEST(test_default_iterator_not_equal_list_iterator) {
    List<int>::Iterator def_it;
    List<int> list;
    list.push_back(1);
    auto list_it = list.begin();
    ASSERT_TRUE(def_it != list_it);
}


TEST_MAIN();