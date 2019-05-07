# optimization_demo
A demo to show some optimization methods in C/C++ development.

### Build
```
sudo apt install libgoogle-glog-dev
git clone https://github.com/jingedawang/optimization_demo.git
cd optimization_demo
mkdir build
cd build
cmake ..
make
```

### Usage
```
./optimization_demo
```

### Methods compared in the demo
+ `trival`: Trival implementation.
+ `trival_bad`: Trival implementation but accumulated on memory variable.
+ `outofloop`: Move common operation outside of loop.
+ `direct_access`: Direct access to vector data instead of using `operator[]`.
+ `unroll_2`: Unroll loop by 2.
+ `unroll_3`: Unroll loop by 3.
+ `unroll_4`: Unroll loop by 4.
+ `auto_unroll`: Auto unroll loop by compiler. (Seems not work properly)
+ `u_2_p_2`: Unroll loop by 2, 2-way parallelism.
+ `u_3_p_3`: Unroll loop by 3, 3-way parallelism.
+ `u_2_reasso`: Unroll loop by 2, change associativity of addition operation.
+ `final`: Unroll loop by 4, change associativity of addition operation.

### Performance result
```
-----------------------------------------------------------------------------------Time used--------------------------------------------------------------------------------
-- trival       trival_bad   outofloop    direct_accessunroll_2     unroll_3     unroll_4     auto_unroll  u_2_p_2      u_3_p_3      u_2_reasso   final        Total        
-- 0.00454631   0.00493059   0.0028528    0.00175893   0.00115604   0.000894822  0.000764099  0.00181297   0.00141279   0.000973887  0.000989889  0.000683308  0.0227764    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
```
