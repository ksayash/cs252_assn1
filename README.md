# CS252 Assignment 1
Assignment 1 submission by team '3 Musketeers', consisting of 4 members -- Sayash, Navya, Abhishek and Vinayak

### Displaying pictures of cats and dogs, cars and trucks
A client can enter a query in any form, such as `4 dogs 2 cats` and the corresponding images will be displayed in a browser.

### Aesthetically pleasing
These images are rendered based on the query and adapt dynamically to look good based on the number of images to be received.

### Dockerizing the server
- Firstly, build the server image: 
```docker build -t server_image ./  ```
- Run the server image: 
  ```docker run -it -p 5432:5432 server_image bash```
- In docker conatiner: 
  ```./server```
- On local machine: 
```./client```
(after compilation)  
