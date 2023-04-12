# write_shit_to_disk

## System Require

linux with gcc

## Compile

gcc main.c -lz

## Usage

        Usage: ./a.out <n_byte> <time>

          Write <n_byte> bytes from memory to a tmp_file <time> times, print time to console.
        
# Example

```
./a.out 1000000000 1

CPU time: 0.434367 sec
Real time: 0.435269 sec

```


```
./a.out 1000000000 1

CPU time: 0.436317 sec
Real time: 0.436306 sec

```
