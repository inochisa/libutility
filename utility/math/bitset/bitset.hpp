
#ifndef __UTILITY_BITSET__
#define __UTILITY_BITSET__ 1L

#include<utility/config/utility_config.hpp>

#ifndef BITSET_NO_NEED_STRING
# include<string>
#endif // ! BITSET_NO_NEED_STRING

#ifndef BITSET_NO_NEED_IO
#include<istream>
#include<ostream>
#endif // ! BITSET_NO_NEED_IO



namespace utility
{
  namespace math
  {
    using size_t = decltype(0UL);

    template
    <
      size_t Size,
      typename bit_type = unsigned long,
      typename trait = ::utility::trait::math::bit_trait<bit_type>
    >
    class bitset;
  }
}

namespace utility
{
  namespace math
  {
    template<size_t Size, typename bit_type, typename trait>
    class bitset
    {

      static_assert(utility::trait::type::is_same<bit_type, typename trait::type>::value, "The trait doesn't match the type");
      static_assert(trait::vaild, "The type doesn't support bitset");
      static_assert(trait::bitoperation, "The type doesn't support bit operation");

      public:
        typedef trait       bit_info;
        typedef bit_type    bit_type;
        typedef size_t      size_type;

      public:
        constexpr static size_type npos = static_cast<size_t>(-1);

      private:
        typedef trait       info;

      public:
        class reference
        {
          friend class bitset<size, bit_type, trait>;
          private:
            bit_type& bit_block;
            const bit_type bit_mask;

          private:
            reference(bit_type& bit_val, bit_type pos):
              bit_block(bit_val),
              bit_mask( bit_type(1) << pos)
            { }

          public:
            operator bool() const noexcept
            { return this->bit_block & this->bit_mask;}
            bool operator~() const noexcept
            { return !(this->bit_block & this->bit_mask);}

            reference& operator= (bool flag) noexcept
            { this->do_assign(flag); return *this;}
            reference& operator= (const reference& rhs) noexcept
            { this->do_assign(rhs); return *this;}
            reference& operator|= (bool flag) noexcept
            {
              if(flag)
              { this->do_set();}
              return *this;
            }
            reference& operator&= (bool flag) noexcept
            {
              if(!flag)
              { this->do_reset();}
              return *this;
            }
            reference& operator^= (bool flag) noexcept
            {
              if(flag)
              { this->do_filp();}
              return *this;
            }
            reference& operator-= (bool flag) noexcept
            {
              if(flag)
              { this->do_reset();}
              return *this;
            }

          public:
            reference& flip() noexcept
            { this->do_filp(); return *this;}

          private:
            void do_set() noexcept
            { this->bit_block |= this->bit_mask;}
            void do_reset() noexcept
            { this->bit_block &= ~(this->bit_mask);}
            void do_filp() noexcept
            { this->bit_block ^= this->bit_mask;}
            void do_assign(bool flag) noexcept
            { flag? this->do_set() : this->do_reset();}
        };

      private:
        bit_type blocks[Size/(trait::bitlen)+1];
        const size_type size = Size;



      public:
        constexpr bitset();
        constexpr explicit bitset(bit_type val);

#ifndef BITSET_NO_NEED_STRING
      public:
        // Construct bitset from the pos of string, the length is n
        template<typename CharT, typename Traits, typename Alloc>
        explicit bitset(
          const std::basic_string<CharT, Traits, Alloc>& str,
          typename std::basic_string<CharT, Traits, Alloc>::size_type pos,
          typename std::basic_string<CharT, Traits, Alloc>::size_type n,
          size_type num_bits = npos
        );

        // Construct bitset from the pos of string, until the end
        template<typename CharT, typename Traits, typename Alloc>
        explicit bitset(
          const std::basic_string<CharT, Traits, Alloc>& str,
          typename std::basic_string<CharT, Traits, Alloc>::size_type pos = 0
        )
#endif

      public:
        bitset(unsigned long long);
        bitset(const bitset&);
        bitset(bitset&&);
        bitset& operator= (const bitset&);
        bitset& operator= (bitset&&);
      public:
        ~bitset();

      public:
        bitset& operator&= (const bitset&);
        bitset& operator|= (const bitset&);
        bitset& operator^= (const bitset&);
        bitset& operator<<= (size_type);
        bitset& operator>>= (size_type);
        bitset operator<< (size_type) const;
        bitset operator>> (size_type) const;

      public:
        bitset& operator~() const;

      public:
        reference operator[](size_type pos)
        { return reference(
          this->blocks[this->block_index(pos)], this->block_mask(pos));}
        inline bool operator[](size_type pos) const
        { return this->test(pos);}

      public:
        bitset& set();
        bitset& set(size_type);
        bitset& reset();
        bitset& reset(size_type);
        bitset& flip();
        bitset& flip(size_type);

      public:
        bool test(size_type pos) const;
        bool all() const;
        bool any() const;
        bool none() const;

      public:
        size_type count() const noexcept;
        size_type size() const noexcept
        { return this->size/(trait::bitlen)+1;}
        size_type length() const noexcept
        { return this->size;}

      public:
        size_type find_first() const;
        size_type find_next(size_type pos) const;

      public:
        unsigned long to_ulong;
        unsigned long long to_ullong;

      public:
        template<size_t T1, size_t T2, typename _bit, typename _bit_trait>
        friend bool operator== (
          const bitset<T1, _bit, _bit_trait>&,
          const bitset<T2, _bit, _bit_trait>&
        );

      private:
        static size_type block_index(size_type pos) noexcept
        { return pos / trait::bitlen;}
        static bit_type block_mask(size_type pos) noexcept
        { return pos % trait::bitlen;}
        static bit_type bit_mask(size_type pos) noexcept
        { return bit_type(1) << pos;}

      private:
        void init_from_ullong(unsigned long long);
    };

    template<size_t Size, typename bit_type, typename trait>
    void bitset<Size, bit_type, trait>::init_from_ullong(
      unsigned long long val)
    {
    }
  }
}



#endif // ! __UTILITY_BITSET__
