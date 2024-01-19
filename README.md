# A simple tool to calculate CRC

**crc** is a simple program to calculate CRC values created to simplify some of
my work routines. Currently it only supports CRC-16-CCITT-FALSE because that's
all that I've required at work. But the code is written in a way that it should
be easy to add other CRC algorithms.

## Compiling

`make`

## Installing

`PREFIX=~/.local make install` or `PREFIX=/usr make install`. Modify **PREFIX** to your needs.

## Usage

- `crc <hex-value>` To generate a crc from a hex value. Eg. `crc beef1234`
- `crc -h` To print help
- `crc -l` To list supported CRC algorithms

### Generating a CRC

- `crc beef1234` will output `488d`

### Validating a CRC

The CRC of a value with CRC appended to it should be 0. Eg. `crc beef1234488d` will output `0`.

## Contributing

Yes please! I'm happy to accept pull requests.
