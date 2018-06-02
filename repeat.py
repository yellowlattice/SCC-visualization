res_list = []  

f = open('C:/Users/lenovo/Desktop/force/res.txt','r')  
res_dup = []  
index = 0  
file_dul = open('C:/Users/lenovo/Desktop/force/clean.txt', 'w')  
for line in f.readlines():    
    if line not in res_list:     
        file_dul.write(line)                        
        res_list.append(line)  
