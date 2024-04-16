#include "my_personlib.h"

int main()
{
    struct staff* s = new_staff();

    staff_append_member(s, new_member("lionel", "auroux", "1977-10-05"));
    staff_append_member(s, new_member("samuel", "lemarchand", "1980-05-25"));
    staff_append_member(s, new_member("sophie", "labadie", "1979-08-13"));
    staff_append_member(s, new_member("marie", "chazan", "1981-02-19"));

    staff_insert_after_member_name(s, "lionel", new_member("theo", "abel", "2001-07-13"));
}