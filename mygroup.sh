# create cgroup and add cpu, memory limit
# cpu limit = 30%
# memory limit = 64k
mkdir /sys/fs/cgroup/cpu/mygroup
echo 30000 > /sys/fs/cgroup/cpu/mygroup/cpu.cfs_quota_us 
mkdir /sys/fs/cgroup/memory/mygroup
echo 655360 > /sys/fs/cgroup/memory/mygroup/memory.limit_in_bytes 