# CS252 Assignment 1
Assignment 1 submission by team '3 Musketeers', consisting of 4 members -- Sayash, Navya, Abhishek and Vinayak

### Server Response
The Server sends the asked number of images to the client(file transfer), the client temporarily stores them inside his directory, forms the aesthetically pleasant html page, and renders it in the browser.

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

### Constraints-
As written in the Assignment writeup, the number of images asked for any category can't be more than 4. It can be in range [0,4]. Sending query of more than 4 images will result in error, and we have not done error handling as of now, since assignment doesn't demand it. 

