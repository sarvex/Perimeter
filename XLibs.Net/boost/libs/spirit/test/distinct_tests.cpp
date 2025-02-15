/*=============================================================================
    Copyright (c) 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/distinct.hpp>
#include <boost/test/included/unit_test_framework.hpp>

using namespace boost;
using namespace unit_test_framework;
using namespace spirit;

typedef
    scanner<char const*, scanner_policies<skipper_iteration_policy<> > >
        scanner_t;

typedef
    rule<scanner_t>
        rule_t;

void distinct_parser_test()
{
    // distinct_parser()
    {
        distinct_parser<> distinct_p;

        // operator()(CharT const* str) const
        rule_t r = distinct_p("keyword") >> !ch_p('-') >> int_p;
        BOOST_CHECK(parse("keyword123", r, space_p).full);
    }

    // distinct_parser(CharT const* letters)
    {
        distinct_parser<> distinct_p("0-9a-zA-Z_");

        // operator()(CharT const* str) const
        rule_t r = distinct_p("keyword") >> !ch_p('-') >> int_p;
        BOOST_CHECK(parse("keyword 123", r, space_p).full);
        BOOST_CHECK(parse("keyword-123", r, space_p).full);
        BOOST_CHECK(!parse("keyword123", r, space_p).hit);
    }

    // distinct_parser(parser<TailT> const & tail_)
    {
        distinct_parser<
            char,
            alternative<
                alnum_parser,
                sequence<
                    chlit<>,
                    negated_char_parser<chlit<> >
                >
            >
        >
            distinct_p(alnum_p | ('-' >> ~ch_p('-')));

        // operator()(CharT const* str) const
        rule_t r = distinct_p("keyword") >> !str_p("--") >> int_p;
        BOOST_CHECK(parse("keyword 123", r, space_p).full);
        BOOST_CHECK(parse("keyword--123", r, space_p).full);
        BOOST_CHECK(!parse("keyword-123", r, space_p).hit);
    }
}

void distinct_directive_test()
{
    // distinct_directive()
    {
        distinct_directive<> distinct_d;

        // operator[](CharT const* str) const
        {
            rule_t r = distinct_d["keyword"] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword123", r, space_p).full);
        }

        // operator[](parser<ParserT> const &subject) const
        {
            rule_t r = distinct_d[str_p("keyword")] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword123", r, space_p).full);
        }
    }

    // distinct_directive(CharT const* letters)
    {
        distinct_directive<> distinct_d("0-9a-zA-Z_");

        // operator[](CharT const* str) const
        {
            rule_t r = distinct_d["keyword"] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword-123", r, space_p).full);
            BOOST_CHECK(!parse("keyword123", r, space_p).hit);
        }

        // operator[](parser<ParserT> const &subject) const
        {
            rule_t r = distinct_d[str_p("keyword")] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword-123", r, space_p).full);
            BOOST_CHECK(!parse("keyword123", r, space_p).hit);
        }
    }

    // distinct_directive(parser<TailT> const & tail_)
    {
        distinct_directive<
            char,
            alternative<
                alnum_parser,
                sequence<
                    chlit<>,
                    negated_char_parser<chlit<> >
                >
            >
        >
            distinct_d(alnum_p | ('-' >> ~ch_p('-')));

        // operator[](CharT const* str) const
        {
            rule_t r = distinct_d["keyword"] >> !str_p("--") >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword--123", r, space_p).full);
            BOOST_CHECK(!parse("keyword-123", r, space_p).hit);
        }

        // operator[](parser<ParserT> const &subject) const
        {
            rule_t r = distinct_d[str_p("keyword")] >> !str_p("--") >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword--123", r, space_p).full);
            BOOST_CHECK(!parse("keyword-123", r, space_p).hit);
        }
    }
}

void dynamic_distinct_parser_test()
{
    // dynamic_distinct_parser()
    {
        dynamic_distinct_parser<scanner_t> distinct_p;

        // operator()(CharT const* str) const
        rule_t r = distinct_p("keyword") >> !ch_p('-') >> int_p;
        BOOST_CHECK(parse("keyword123", r, space_p).full);
    }

    // dynamic_distinct_parser(CharT const* letters)
    {
        dynamic_distinct_parser<scanner_t> distinct_p("0-9a-zA-Z_");

        // operator()(CharT const* str) const
        rule_t r = distinct_p("keyword") >> !ch_p('-') >> int_p;
        BOOST_CHECK(parse("keyword 123", r, space_p).full);
        BOOST_CHECK(parse("keyword-123", r, space_p).full);
        BOOST_CHECK(!parse("keyword123", r, space_p).hit);
    }

    // dynamic_distinct_parser(parser<TailT> const & tail_)
    {
        dynamic_distinct_parser<scanner_t>
            distinct_p(alnum_p | ('-' >> ~ch_p('-')));

        // operator()(CharT const* str) const
        rule_t r = distinct_p("keyword") >> !str_p("--") >> int_p;
        BOOST_CHECK(parse("keyword 123", r, space_p).full);
        BOOST_CHECK(parse("keyword--123", r, space_p).full);
        BOOST_CHECK(!parse("keyword-123", r, space_p).hit);
    }
}

void dynamic_distinct_directive_test()
{
    // dynamic_distinct_directive()
    {
        dynamic_distinct_directive<scanner_t> distinct_d;

        // operator[](CharT const* str) const
        {
            rule_t r = distinct_d["keyword"] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword123", r, space_p).full);
        }

        // operator[](parser<ParserT> const &subject) const
        {
            rule_t r = distinct_d[str_p("keyword")] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword123", r, space_p).full);
        }
    }

    // dynamic_distinct_directive(CharT const* letters)
    {
        dynamic_distinct_directive<scanner_t> distinct_d("0-9a-zA-Z_");

        // operator[](CharT const* str) const
        {
            rule_t r = distinct_d["keyword"] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword-123", r, space_p).full);
            BOOST_CHECK(!parse("keyword123", r, space_p).hit);
        }

        // operator[](parser<ParserT> const &subject) const
        {
            rule_t r = distinct_d[str_p("keyword")] >> !ch_p('-') >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword-123", r, space_p).full);
            BOOST_CHECK(!parse("keyword123", r, space_p).hit);
        }
    }

    // dynamic_distinct_directive(parser<TailT> const & tail_)
    {
        dynamic_distinct_directive<scanner_t>
            distinct_d(alnum_p | ('-' >> ~ch_p('-')));

        // operator[](CharT const* str) const
        {
            rule_t r = distinct_d["keyword"] >> !str_p("--") >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword--123", r, space_p).full);
            BOOST_CHECK(!parse("keyword-123", r, space_p).hit);
        }

        // operator[](parser<ParserT> const &subject) const
        {
            rule_t r = distinct_d[str_p("keyword")] >> !str_p("--") >> int_p;
            BOOST_CHECK(parse("keyword 123", r, space_p).full);
            BOOST_CHECK(parse("keyword--123", r, space_p).full);
            BOOST_CHECK(!parse("keyword-123", r, space_p).hit);
        }
    }
}

test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
    test_suite* test = BOOST_TEST_SUITE("distinct test");

    test->add(BOOST_TEST_CASE(&distinct_parser_test));
    test->add(BOOST_TEST_CASE(&distinct_directive_test));
    test->add(BOOST_TEST_CASE(&dynamic_distinct_parser_test));
    test->add(BOOST_TEST_CASE(&dynamic_distinct_directive_test));

    return test;
}

