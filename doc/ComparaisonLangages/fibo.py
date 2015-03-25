def fibo(v):
    if v < 1:
        return 1
    else:
        return(fibo(v-1) + fibo(v-2))

def main(): return fibo(40)

