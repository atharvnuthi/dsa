#Recursive Backtracking
def f(n):
		if n==0: return 0
		if n==1: return 1
		return f(n-1) + f(n-2)

#Top-Down DP (Memoization)
def fib(n):
		memo = {0:0, 1:1}
		def f(n):
				if n in memo:
						return memo[n]
				memo[n] = f(n-1) + f(n-2)
				return memo[n]
		return f(n)
	
#Bottom-Up DP (Tabulation)
def fib(n):
		dp = [0,1]
		for i in range (2, n+1):
				new = dp[i-1] + dp[i-2]
				dp.append(new)
		return dp[n]

#Space Optimized Bottom-Up
def fib(n):
		if n < 2: return n
		prev, cur = 0,1
		for i in range (2, n+1):
				prev, cur = cur, cur + prev
		return cur