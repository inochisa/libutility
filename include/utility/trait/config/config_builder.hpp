
#ifndef ___UTILITY__TRAIT__CONFIG__BUILDER___
#define ___UTILITY__TRAIT__CONFIG__BUILDER___

#include<map>
#include<string>
#include<iostream>

namespace utility
{
  namespace __config
  {
    namespace builder
    {
      void add_identifier(std::map<std::string, int>& __searcher)
      {
        __searcher.insert({"__has_trivial_destructor", 0});
        __searcher.insert({"__has_virtual_destructor", 0});
        __searcher.insert({"__is_abstract", 0});
        __searcher.insert({"__is_aggregate", 0});
        __searcher.insert({"__is_assignable", 0});
        __searcher.insert({"__is_base_of", 0});
        __searcher.insert({"__is_class", 0});
        __searcher.insert({"__is_constructible", 0});
        __searcher.insert({"__is_empty", 0});
        __searcher.insert({"__is_enum", 0});
        __searcher.insert({"__is_literal", 0});
        __searcher.insert({"__is_pod", 0});
        __searcher.insert({"__is_polymorphic", 0});
        __searcher.insert({"__is_standard_layout", 0});
        __searcher.insert({"__is_trivial", 0});
        __searcher.insert({"__is_trivially_assignable", 0});
        __searcher.insert({"__is_trivially_constructible", 0});
        __searcher.insert({"__is_trivially_copyable", 0});
        __searcher.insert({"__is_union", 0});
        __searcher.insert({"__underlying_type", 0});
        // __searcher.insert({"__is_literal_type", 0});
      }

      void add_args(std::map<std::string, int>& __searcher)
      {
        __searcher.insert({"__has_trivial_destructor", 1});
        __searcher.insert({"__has_virtual_destructor", 1});
        __searcher.insert({"__is_abstract", 1});
        __searcher.insert({"__is_aggregate", 1});
        __searcher.insert({"__is_assignable", 2});
        __searcher.insert({"__is_base_of", 2});
        __searcher.insert({"__is_class", 1});
        __searcher.insert({"__is_constructible", -1});
        __searcher.insert({"__is_empty", 1});
        __searcher.insert({"__is_enum", 1});
        __searcher.insert({"__is_literal", 1});
        __searcher.insert({"__is_pod", 1});
        __searcher.insert({"__is_polymorphic", 1});
        __searcher.insert({"__is_standard_layout", 1});
        __searcher.insert({"__is_trivial", 1});
        __searcher.insert({"__is_trivially_assignable", 2});
        __searcher.insert({"__is_trivially_constructible", -1});
        __searcher.insert({"__is_trivially_copyable", 1});
        __searcher.insert({"__is_union", 1});
        __searcher.insert({"__underlying_type", 1});
        // __searcher.insert({"__is_literal_type", 0});
      }

      void outargs(int __tmp)
      {
        using std::cout;
        switch(__tmp)
        {
          case 1:
            std::cout << "(type)";
            break;
          case 2:
            std::cout << "(type1, type2)";
            break;
          case -1:
            std::cout << "(...)";
            break;
          case -2:
            std::cout << "(__VA_ARGS__)";
          default:
            ;
        }
      }

      void transform_macro_build(const std::string& __compiler)
      {
        using std::cin; using std::cout;
        using std::string;
        std::map<string, int> rec;
        std::map<string, int> arec;
        add_identifier(rec);
        add_args(arec);
        cout << "#ifdef " << __compiler << "\n";
        cout << "#define __utility_support_compile_extension 1" << "\n";
        string str;
        while(cin >> str)
        {
          if(str == "__is_literal_type")
          {
            rec["__is_literal"] = 2;
            continue;
          }
          if(!rec.count(str))
          { continue;}
          rec[str] = 1;

        }
        for(const auto& now : rec)
        {
          cout << "#define __utility_has" << now.first.substr(1) << " ";
          cout << now.second;
          cout << "\n";
        }
        cout << "\n";
        for(const auto& now : rec)
        {
          if(now.second)
          {
            cout << "#define __utility" << now.first.substr(1);
            outargs(arec[now.first]);
            cout << " ";
            cout << now.first;
            if(now.second == 2)
            {
              cout << "_type";
            }
            outargs(arec[now.first] < 0 ? -2 : arec[now.first]);
            cout << "\n";
          }
        }
        cout << "#endif" << " // ! " << __compiler << "\n";
      }

      void undefine_macro_build(const std::string& __compiler)
      {
        using std::cin; using std::cout;
        using std::string;
        std::map<string, int> rec;
        add_identifier(rec);
        string str;
        while(cin >> str)
        {
          if(str == "__is_literal_type")
          {
            rec["__is_literal"] = 2;
            continue;
          }
          if(!rec.count(str))
          { continue;}
          rec[str] = 1;
        }
        cout << "#ifdef " << __compiler << "\n";
        for(const auto& now : rec)
        {
          if(now.second)
          {
            cout << "#undef __utility" << now.first.substr(1);
            cout << "\n";
          }
        }
        cout << "#endif" << " // ! " << __compiler << "\n";
      }

      void undefine_macro_build()
      {
        using std::cin; using std::cout;
        using std::string;
        std::map<string, int> rec;
        add_identifier(rec);
        for(const auto& now : rec)
        {
          cout << "#undef __utility_has" << now.first.substr(1);
          cout << "\n";
        }
        cout << "#undef __utility_support_compile_extension" << "\n";
      }

      void othercompiler()
      {
        using std::cout;
        using std::string;
        std::map<string, int> rec;
        add_identifier(rec);
        cout << "#ifndef __utility_support_compile_extension" << "\n";
        cout << "#define __utility_support_compile_extension 0" << "\n";
        for(const auto& now : rec)
        {
          cout << "#define __utility_has" << now.first.substr(1) << " ";
          cout << now.second;
          cout << "\n";
        }
        cout << "#endif // __utility_support_compile_extension" << "\n";
      }
    }
  }
}
/*
GNU support
__is_enum
__is_union
__is_class
__is_trivial
__is_trivially_copyable
__is_standard_layout
__is_pod
__is_literal_type
__is_empty
__is_polymorphic
__is_abstract
__is_constructible
__is_assignable
__is_trivially_constructible
__is_trivially_assignable
__has_trivial_destructor
__has_virtual_destructor
__is_base_of
__underlying_type
__is_aggregate

MSVC support
__has_trivial_destructor
__has_virtual_destructor
__is_abstract
__is_aggregate
__is_assignable
__is_base_of
__is_class
__is_constructible
__is_empty
__is_enum
__is_pod
__is_polymorphic
__is_union

Clang support
__has_trivial_destructor
__has_virtual_destructor
__is_abstract
__is_aggregate
__is_assignable
__is_base_of
__is_class
__is_constructible
__is_empty
__is_enum
__is_literal
__is_pod
__is_polymorphic
__is_trivially_assignable
__is_trivially_constructible
__is_union
__underlying_type
*/

#endif // ! ___UTILITY__TRAIT__CONFIG__BUILDER___
