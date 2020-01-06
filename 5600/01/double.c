long
dub(long x)
{
    return x + x;
}

int
main(int _argc, char* _argv[])
{
    long x = dub(5);
    printf("%ld\n", x);
    return 0;
}
