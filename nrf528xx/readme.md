# nrf528xx subdirectory

## building

```bash
# build for big dev board
west build -b nrf52833dk_nrf52833

# build for usb dongle
west build -b nrf52840dongle_nrf52840
```

## flashing

```bash
# incremental flash
west flash

# force erase flash first
west flash --erase
```

