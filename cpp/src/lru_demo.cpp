//
// Created by dupen on 2020/3/28.
//
#include <string>
#include <unordered_map>
#include <iostream>

#include "../include/lru.h"

using namespace std;
using namespace proalg;


int main() {

    LRUCache<string, string> lru(3);

    unordered_map<string, string> msg = {
        {"put", "[put] size: "},
        {"get", "[get] value: "},
        {"cap", "[cap] "}
    };

    try {
        cout << msg["put"] << lru.Put("aaa", "AAA") << endl;
        cout << lru["aaa"] << endl;
        lru["ggg"] = "GGG";
        cout << lru["ggg"] << endl;
        lru["ggg"] = "888";
        cout << lru["ggg"] << endl;
        lru["qzzzz"] = "wdnmd";
        lru["ddddd"] = "DDDDD";
        cout << endl;
        lru.DisplayAll();

        lru["empty value"];
        cout << endl;
        lru.DisplayAll();
        return 0;

        cout << msg["put"] << lru.Put("bbb", "BBB") << endl;
        cout << msg["put"] << lru.Put("ccc", "CCC") << endl;

        cout << msg["get"] << lru.Get("aaa") << endl;

        cout << msg["put"] << lru.Put("ddd", "DDD") << endl;
        cout << "------------------" << endl;
        lru.DisplayAll();
        cout << "------------------" << endl;
        cout << msg["get"] << lru.Get("bbb") << endl;       // not exists


        cout << msg["cap"] << lru.GetCapacity() << endl;
        lru.SetCapacity(5);
        cout << msg["cap"] << lru.GetCapacity() << endl;

        cout << msg["put"] << lru.Put("zxc", "ZXC") << endl;
        cout << msg["put"] << lru.Put("asd", "ASD") << endl;
        cout << msg["get"] << lru.Get("aaa") << endl;
        cout << msg["put"] << lru.Put("qwe", "QWE") << endl;

        cout << "------------------" << endl;
        lru.DisplayAll();
        cout << "------------------" << endl;
        //cout << msg["get"] << lru.Get("ccc") << endl;   // not exists

        cout << lru.IsExists("ccc") << endl;

        lru.Clear();
        cout << msg["put"] << lru.Put("tom", "jerry") << endl;
    }
    catch (const ElemNotExistsException &e) {
        cout << "error: " << e.what() << endl;
    }

    return 0;
}
