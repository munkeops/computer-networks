import random
  
# using list comprehension + randrange()  
# to generate random number list 
len=random.randrange(25,100)
res = [random.randrange(1, 100, 1) for i in range(len)] 

print (len,res)