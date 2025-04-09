### 8 Apr. 2025

#### $J/\psi+J/\psi+\Upsilon$的更新

![First_J_J_Y_fit](images/J+J+Y_2022_2023_2024_Fit_01.png)

设定如下：

* $J/\psi : p_T > 4 \space \mathrm{GeV/c}, |\eta| < 2.5$
* $\Upsilon : p_T > 3 \space \mathrm{GeV/c}, p_{\mu, T} > 4 \space \mathrm{GeV/c}, |\eta| < 2.5$
* PDF for fitting: 
    * Signal: Gaussian
    * Background: 2nd-order polynomial

产额参考数据如下：

```bash
yield_BBB         = 506.232      +/-  27.6162   (limited)
yield_BBS         = 57.7191      +/-  11.6531   (limited)
yield_BSB         = 22.8468      +/-  9.01032   (limited)
yield_BSS         = 3.48014      +/-  3.97018   (limited)
yield_SBB         = 50.7352      +/-  14.4413   (limited)
yield_SBS         = 5.97737      +/-  5.00817   (limited)
yield_SSB         = 0.000206299  +/-  7.75929   (limited)
===== Significance Calculation =====
Log-likelihood (S+B): 2759.3
Log-likelihood (B only): 2759.3
Delta Log-likelihood: 6.65403e-05
Significance: 0.0115361 sigma
```

yield_SSS甚至没有直接给出值...图中写的是$0\pm2$...

以上的信号都是用的是Gaussian而不是CB，而且$\Upsilon(2S, 3S)$的峰还没有加入，但是预期改善不大。作为报告的话...“声明现阶段不宜看这个反应”？产生截面上限值如何估计？

> $\Upsilon(1S)$原本截面就很低，给出的$\sigma_{\mathrm{eff}}$的下限限制应该会很低，继续做这个过程的意义大吗？

#### 问题：关于Trigger引起的质量分布bias（？）

查阅CMS HLT info得知，`HLT_Dimuon0_Jpsi3p5_Muon2_v`里面的触发条件中，要求存在一对质量在2.95 GeV至3.25 GeV之间的正反muon对；`HLT_DoubleMu4_3_LowMass_v`的不变质量限制则更宽一些，为0.2 GeV 至8.5 GeV。如果选择质量窗为$[2.0, 4.0]$，我们将有机会看到$[2.95,3.25]$区间出现“本底抬高”吗？

> 虽然说之前看到单独使用`HLT_Dimuon0_Jpsi3p5_Muon2_v`的时候旁边的本底也不那么高？

#### 问题：关于使用HELAC-Onia

1. 如何产生含有$\phi(1020)$样本的事例？
2. 产生的TPS样本里面，$J/\psi$和$\Upsilon(1S)$单独的动力学分布已经和单独产生的分布不太一致。如何理解？是不是和选择的部分子分布函数有关系，还是说“存在另外两个粒子”就是一种条件关联？
3. 更换随机种子却得到相同的结果，这是为什么？

又：正在尝试做triple-$J/\psi$的复现，测试工作进行中。



