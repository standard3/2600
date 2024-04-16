extern unsigned long my_fibo(unsigned long __n)
{
    if (__n == 0) 
        return 0;
    else if (__n == 1)
        return 1;
    else
        return my_fibo(__n - 1) + my_fibo(__n - 2);
}