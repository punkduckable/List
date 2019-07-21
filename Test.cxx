#include "Node.hxx"
#include "Linked_List.hxx"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Node tests", "[Node]") {
  // First, make some nodes.
  double value1 = 401.28492, value2 = 293.2932;
  Node<double> N1{value1}, N2{value2};

  // Now, check that they were set up correctly.
  REQUIRE( N1.GetItem() == value1 );
  REQUIRE( N2.GetItem() == value2 );
  REQUIRE( N1.GetNext() == NULL );
  REQUIRE( N2.GetNext() == NULL );
} // TEST_CASE("Node tests", "[Node]") {



TEST_CASE("List tests","[List][Insertion]") {
  // First, make two lists
  Linked_List<double> L1{}, L2{};

  // Add the first item to L1 using append, to L2 using prepend.
  double value1 = 129392.392;
  REQUIRE( L1.GetLength() == 0 );
  L1.Append(value1);
  L2.Prepend(value1);
  REQUIRE( L1.GetLength() == 1 );
  REQUIRE( L2.GetLength() == 1 );

  // Now, prepend a 2nd item onto L1, append a 2nd onto L2
  double value2 = 2934203.248203;
  L1.Prepend(value2);
  L2.Append(value2);
  REQUIRE( L1.GetLength() == 2 );
  REQUIRE( L2.GetLength() == 2 );

  /* At this point, L1 should look like
        L1: value2 <-> value1
  and L2 should look like
        L2: value1 <-> value2
  Let's check that both values can be found in the list and that searching for
  an item that isn't in the list returns nullptr */
  REQUIRE( L1.Search(value1) != nullptr );
  REQUIRE( L1.Search(value2) != nullptr );
  REQUIRE( L1.Search(value1 + 1) == nullptr );

  /* Now, let's check that the ordering of the nodes is correct */
  REQUIRE( L1.Search(value2)->GetNext() == L1.Search(value1) );
  REQUIRE( L2.Search(value1)->GetNext() == L2.Search(value2) );


  /* Now, check that the [] operators work for accessing values. */
  REQUIRE( L2[0]->GetItem() == value1 );
  REQUIRE( L2[1]->GetItem() == value2 );

  /* Now, let's try removing the items and testing that the list updates the
  way that it should. */
  L1.Append(value1);    /* List should now be value2 <-> value1 <-> value1 */
  REQUIRE( L1.GetLength() == 3 );
  REQUIRE( L1[2]->GetItem() == value1 );
  L1.Remove(value1);    /* List should now be value2 */
  REQUIRE( L1.GetLength() == 1 );
  REQUIRE( L1.Search(value1) == nullptr );
  REQUIRE( L1.Search(value2) != nullptr );
  REQUIRE( L1[0]->GetItem() == value2 );
  L1.Remove(value2);    /* List should now be empty */
  REQUIRE( L1.GetLength() == 0 );
  REQUIRE( L1.Search(value2) == nullptr );
} // TEST_CASE("List insertion tests","[List][Insertion]") {
