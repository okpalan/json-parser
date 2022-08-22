#ifndef json_h
#define json_h

#include <stdio.h>

#define jsonp_malloc malloc
#define jsonp_free free
#define jsonp_strdup strdup

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        json_type_boolean,
        json_type_double,
        json_type_int,
        json_type_string,
        json_type_object
    } json_type;

    typedef struct json_object
    {
        struct json_object *_next;
        struct json_object *_prev;
        json_type o_type;
        int _ref_count;

        union data
        {
            struct
            {
                char *buf;
                int len;
            } _string;

            struct
            {
                struct json_object *head;
                struct json_object *tail;
            } _object;

            struct
            {
                double d;
            } _double;

            struct
            {
                int i;
            } _int;

            struct
            {
                int b;
            } _boolean;

        } o;

    } json_object;

    extern struct json_object *json_object_new_string(const char *s);
    extern struct json_object *json_object_new_object();
    extern void json_object_generic_delete(struct json_object *jso);
    extern int json_object_get_ref_count(struct json_object *jso);
    extern size_t json_object_to_json_string_len(struct json_object *jso);
    extern char *json_stringify(json_object *object);
    extern int json_object_put(struct json_object *jso);

#ifdef __cplusplus
}
#endif

#endif /* json_h */