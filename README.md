# Slick storage engine

An experimental LSM-Tree database that splits the keys and the values to reduce write and space
amplification. This project is a C implementation of: [WiscKey: Separating Keys from Values
in SSD-conscious Storage](https://www.usenix.org/system/files/conference/fast16/fast16-papers-lu.pdf) (Lu et al. 2017).


## Citations
Lu, Pillai, T., Gopalakrishnan, H., Arpaci-Dusseau, A., & Arpaci-Dusseau, R. (2017). WiscKey: Separating Keys from Values in SSD-Conscious Storage. ACM Transactions on Storage, 13(1), 1–28. https://doi.org/10.1145/3033273

