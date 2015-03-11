function fibo(n) {
    if(n < 1) {
	return 1;
    } else {
	return fibo(n-2) + fibo(n-1);
    }
}
