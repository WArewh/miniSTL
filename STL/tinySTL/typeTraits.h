#ifndef _MYSTL_TYPETRAITS_H
#define _MYSTL_TYPETRAITS_H

namespace mySTL
{

    struct has_true_type
    {
    };
    struct has_false_type
    {
    };

    template <class T>
    struct _type_traits
    {
        using has_trivial_default_constructor = has_false_type;
        using has_trivial_copy_constructor = has_false_type;
        using has_trivial_assignment_operator = has_false_type;
        using has_trivial_destructor = has_false_type;
        using is_POD_type = has_false_type;
    };

    template <>
    struct _type_traits<bool>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<char>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<unsigned char>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<signed char>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<wchar_t>

    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<short>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<unsigned short>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<int>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<unsigned int>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<long>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<unsigned long>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<long long>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<unsigned long long>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<float>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<double>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<long double>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };



    template <class T>
    struct _type_traits<T*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <class T>
    struct _type_traits<const T*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<char*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<unsigned char*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<signed char*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<const char*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<const unsigned char*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

    template <>
    struct _type_traits<const signed char*>
    {
        using has_trivial_default_constructor = has_true_type;
        using has_trivial_copy_constructor = has_true_type;
        using has_trivial_assignment_operator = has_true_type;
        using has_trivial_destructor = has_true_type;
        using is_POD_type = has_true_type;
    };

}  // namespace mySTL

namespace mySTL
{
    //类型退化的traits

    template <typename T>
    struct remove_reference
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&>
    {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;


    template <class T>
    struct remove_cv
    {
        typedef T type;
    };
    template <class T>
    struct remove_cv<const T>
    {
        typedef T type;
    };
    template <class T>
    struct remove_cv<volatile T>
    {
        typedef T type;
    };
    template <class T>
    struct remove_cv<const volatile T>
    {
        typedef T type;
    };
    template <class T>
    using remove_cv_t = typename remove_cv<T>::type;

}  // namespace mySTL

namespace mySTL
{
    //类型添加的traits

    template <typename T>
    struct add_rvalue_reference
    {
        using type = T&&;
    };

    template <typename T>
    using add_rv_ref_t = typename add_rvalue_reference<T>::type;

    template <typename T>
    typename add_rvalue_reference<T>::type declval();

}  // namespace mySTL

namespace mySTL
{
    //类型判断的traits

    template <typename T, T val>
    struct integral_constant
    {
        static const T value = val;
        using value_type = T;
        using type = integral_constant<T, val>;

        constexpr operator value_type() { return value; }

        constexpr value_type operator()() { return value; }
    };

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    template <typename T, typename U>
    struct is_same : public false_type
    {
    };

    template <typename T>
    struct is_same<T, T> : public true_type
    {
    };

    template <class T>
    struct is_void : is_same<void, typename remove_cv<T>::type>
    {
    };



}  // namespace mySTL

#endif