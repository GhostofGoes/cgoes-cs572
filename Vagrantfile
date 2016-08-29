# -*- mode: ruby -*-
# vi: set ft=ruby :
# CS 572 - Evolutionary Computation
# This will setup the environment I develop in

Vagrant.configure("2") do |config|

  config.vm.box = "ubuntu/trusty64"
  config.vm.host_name = "cgoes-cs572-devbox"
  config.vm.synced_folder "../devbox_shared_data", "/shared_data"

  # VirtualBox configuration. You can also use VMWare products, if you have $80 laying around.
  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.memory = "2048"
    vb.cpus = 2
    vb.name = "cs572-devbox"
  end

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update -y
	apt-get upgrade -y
	apt-get dist-upgrade -y
    apt-get install -y  g++-4.9
  SHELL
end
