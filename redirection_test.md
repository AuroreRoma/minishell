# List test

```
2 < word	| ok
2 <			| error
< word		| ok
2 << word	| ok
2 <<		| error
<< word		| ok
2 > word 	| ok
2 >		 	| error
> word	 	| ok
2 >> word	| ok
2 >>		| error
>> word		| ok
><			| error
<>			| error
<<<			| error
>>>			| error
```
