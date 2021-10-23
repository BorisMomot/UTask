package main

import "github.com/spf13/viper"

type UConfig struct {}

func NewUConfig() *UConfig {
	return &UConfig{}
}

func (c *UConfig) GetMaxMediaSize() int {
	return viper.Get("media.maxsize").(int)
}

func (c *UConfig) GetMaxMediaCount() int {
	return viper.Get("media.maxcount").(int)
}
