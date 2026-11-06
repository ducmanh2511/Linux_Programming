# Read File at a Specified Position

Read a specified number of bytes from a file using `SET`, `CUR`, or `END` as the reference point.

## Build

```bash
make all
```

## Run

```bash
./t <file_path> <offset> <number_bytes> <SET|CUR|END>
```

- `file_path`: Path to the file.
- `offset`: Byte offset relative to the selected reference point.
- `number_bytes`: Number of bytes to read.
- `SET`: Beginning of the file.
- `CUR`: Current file position.
- `END`: End of the file.

## Example

```bash
./t test.txt 5 10 SET
./t test.txt -10 10 END
```
