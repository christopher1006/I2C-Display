# I2C-Display
Using OLED I2C screens driven by an Arduino to make custom images for Star Citizen.

Credit to Adafruit for the I2C libraries and  used in this project.

If you want the base file from Adafruit to for their I2C demo, use the ssd1306_128x64_i2c.ino file under `I2C Resources/ ssd1306_128x64_i2c`. Otherwise, use the .ino files from `MISC_Ads` and `Origin_Ads`.

If you want to make your own, you need to create a bitmap that will fit into a 128x64 frame. You may need to invert the image to get it recognized and you may have to edit the picture several times to remove jagged edges.
