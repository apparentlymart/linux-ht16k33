#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/i2c.h>

static struct i2c_device_id ht16k33_idtable[] = {
    { "ht16k33", 0x70 },
    { }
};

MODULE_DEVICE_TABLE(i2c, ht16k33_idtable);

int ht16k33_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    unsigned char *buf;

    buf = devm_kzalloc(&client->dev, 16, GFP_KERNEL);
    if (! buf) {
        return -ENOMEM;
    }

    i2c_set_clientdata(client, buf);

    return 0;
}

int ht16k33_remove(struct i2c_client *client) {

    return 0;
}

static struct i2c_driver ht16k33_driver = {
    .driver = {
        .name = "ht16k33",
        .owner = THIS_MODULE,
    },
    .id_table = ht16k33_idtable,
    .probe = ht16k33_probe,
    .remove = ht16k33_remove,
    .address_list = 0x70,
};

static int __init ht16k33_init(void) {
    printk(KERN_INFO "HT16K33 driver loaded\n");
    return i2c_add_driver(&ht16k33_driver);
}

static void __exit ht16k33_cleanup(void) {
    printk(KERN_INFO "HT16K33 driver unloaded\n");
    i2c_del_driver(&ht16k33_driver);
}

module_init(ht16k33_init);
module_exit(ht16k33_cleanup);

MODULE_AUTHOR("Martin Atkins <mart@degeneration.co.uk>");
MODULE_DESCRIPTION("Driver for HT16K33 LED driver ICs");
MODULE_LICENSE("GPL");

