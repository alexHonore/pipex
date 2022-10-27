# pipex

### Run pipex 
  ```
make && ./pipex infile cmd1 cmd2 outfile
        Act as: > infile cmd1 | cmd2 > outfile
  ```
### How it works

 ```
# ./pipex infile cmd1 cmd2 outfile
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)
```
 
```
  // each cmd needs a stdin (input) and returns an output (to stdout)
   
    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin)
```
### Sources
[Medium zihan tutorial](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)

[Code vault tutorial](https://www.youtube.com/watch?v=6xbLgZpOBi8&t=115s)
