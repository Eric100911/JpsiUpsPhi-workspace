# Triple meson workbook

## Searching for $J/\psi+J/\psi+\Upsilon$ : Looking at individual mass spectra first

### Previous Report (16 Jan. 2025)

<img src="images/prev_report_1.png" alt="截屏2025-02-20 20.23.31" style="zoom:50%;" />

<img src="images/prev_report_2.png" alt="截屏2025-02-20 20.23.37" style="zoom:50%;" />

<img src="images/prev_report_3.png" alt="截屏2025-02-20 20.23.51" style="zoom:50%;" />

<img src="images/prev_report_4.png" alt="截屏2025-02-20 20.23.55" style="zoom:50%;" />

### Dataset and Triggering

Dataset: `ParkingDoubleMuonLowMass[0-7]`

Trigger: in parallel:

* `HLT_Trimuon5_3p5_2_Upsilon_Muon_v`
* `HLT_Dimuon0_Jpsi3p5_Muon2_v`
* `HLT_DoubleMu4_3_LowMass_v`

### Selections

#### "Default" cut for $J/\psi$

* $p_{T} > 6\mathrm{GeV/c}$

* $|\eta| < 2.5$

#### "Default" cut for $\mu^{\pm}$ 

* For $|\eta| < 1.2$, require $p_T > 2.5 \mathrm{GeV/c}$
* For $1.2 < |\eta| < 2.5$, require $p_T > 3.5 \mathrm{GeV/c}$
* Muon ID: soft

#### "Default" cut for vertices

Require a minimal probability of 1%

#### "Default" cut result: 

![SecFilter_nonOverlap](images/JpsiJpsiUps_result_1.png)

Significance for both $J/\psi$, almost no signal in $\Upsilon$ . 

#### Trying cut conditions for $\Upsilon$ (one attempt / 150)

Ups_pt 4.0; Ups_mu_pt 4.0; loose

![SecFilter_nonOverlap](images/JpsiJpsiUps_result_2.png )

Low yield. Looking into setting upper limit for Xsec.



## Searching for $J/\psi+J/\psi+\phi$ : Looking at individual mass spectra first

#### "Default" cut for tracks (assumed to be $K^{\pm}$)

* $p_T > 0.5\mathrm{GeV/c}$

* $|\eta| < 2.5$

#### "Default" cut for $\phi$

* $p_T > 2\mathrm{GeV/c}$

* $|\eta| < 2.5$

#### "Default" result

![d7a9e511a783afae3d11bf95214577d6](images/JpsiJpsiPhi_result_1.PNG)







## Searching for $J/\psi+\Upsilon+\phi$ : Looking on individual mass spectra first

#### "Default" cut result:

![secCut_nonOverlap](images/JpsiUpsPhi_result_1.png)

What the ???



## To resolve:

1. Sorting out multiple candidate. The mass difference might not be goot enough. VtxProb ? $\sum p_T$ ? Also evaluate by doing "best-second-best-comparison"?
2. Correlation matters. Check how $m_{KK}$ peak might change under different VtxProb threshold.
3. Which particle "fires the trigger"? Have a look. Would backgorund from Jpsi trigger on upsilon mass region cause further issue?
4. $\Delta R$ cuts? (may not be as effective)
5. MC studies for characteristics?

## 18 Feb. 2025：来自Alexis和Nuno的建议

### From Alexis

1. 关于multiple candidate的处理方法：贪心算法可能是好的，但是使用的指标可能要另选。$\sum\left[(m_{fit}-m_{\mathrm{PDG}})/(\sigma_{m,fit})\right]^2$作为判据的话，本底的形状很可能会被扭曲（“假峰”），不变质量谱拟合就可能变得不可靠。替代的指标是$\sum p_T$, VtxProb。

2. 续上条，如何判断我们的指标好不好？看看“次优选”和“最优选”的差别如何分布。如果“平滑地差很大”，问题不大(?)

3. 问：使用主要适用于$J/\psi$的trigger，可能是Upsilon信号不显著的原因吗？答：先看看trigger情况。看看触发这个事例的HLT是哪一个，以及是哪些末态粒子参与触发。

    > Q： 如果先去做循环，找Upsilon，可能改善吗？

4. 对于$J/\psi+J/\psi+\phi$，在能够通过加cut找到双$J/\psi$的前提下，考虑在$m_{\mu\mu}$加了质量窗以后，再看看$m_{KK}$。不仅如此，逐渐提升VtxProb阈值，看看$\phi$峰面积如何变化。

5. 对于$\phi$，$K^{\pm}$的$p_T$可以这样约束：对于横动量较大的，要求0.7以上；对于较小的，要求0.5以上。

6. 看看MC。用HELAC-ONIA。

    > Remark: 和赵一扬一起做。必要时联系邵华圣老师（Helac-Onia开发者）以及Alexis.

### From Nuno

1. 我们的径迹拟合结构合适吗？只有$J/\psi$有non-prompt分量，那么$\Upsilon$是不是应该直接把$\mu^{\pm}$往初始顶点拟合，$\phi$是不是应该直接把$K^{\pm}$往初始顶点拟合？

2. $J/\psi$的non-prompt分量用顶点拟合方法合适吗？如果是b-decay，衰变产生的其他粒子带走的动量，会不会影响我们的vertexing？

    > 做得松一点？non-prompt其实寿命也没有太长

3. 有必要尝试复现$3J/\psi$的分析流程吗？

4. 我们处理primary vertex的方式似乎有问题。参考$3J/\psi$的Analysis note。即使是有pileup，我们仍然能判断出有一些“真实的对撞顶点”，我们的primary vertex应该能够归于其中？

    > ![截屏2025-02-19 12.25.19](images/3Jpsi_AN_part_1.png)
    >
    > (From 3J Analysis Note)，可以以后再看

5. 其他可以参考的分析：single- or double-$J/\psi$ + $\phi$ 

6. 看看MC。看看pT等物理量在信号中的分布。

## 20 Feb. 2025 尝试看$J/\psi+\Upsilon+\phi$的一些数据特征

### Trigger

> 这个地方，我们有保留全部的事例吗？是不是那些没有相应HLT的事例已经被丢掉了？

选择`ParkingDoubleMuonLowMass7`在`Run2023D`期间数据，得到以下结果：

```
Number of events: 152176

Number of events triggered by JpsiTrig: 141796
Number of events triggered by UpsTrig:  5932
Number of events triggered by both JpsiTrig and UpsTrig: 0

Number of candidates: 748952
Number of candidates with Jpsi muons that lead to JpsiTrig full: 426603
Number of candidates with Jpsi muons that lead to JpsiTrig mono: 165475
Number of candidates with Jpsi muons that lead to UpsTrig full:  2255
Number of candidates with Jpsi muons that lead to UpsTrig mono:  20568
Number of candidates with Ups muons that lead to JpsiTrig full: 8260
Number of candidates with Ups muons that lead to JpsiTrig mono: 314793
Number of candidates with Ups muons that lead to UpsTrig full:  21648
Number of candidates with Ups muons that lead to UpsTrig mono:  12432
```

如何解读？

我们看Trigger想要回答的问题是，通过了“$J/\psi$触发条件”的事例，是不是会给$\Upsilon$的质量区间，带来较大本底，以至于这些本底的涨落，能够淹没$\Upsilon$信号。

所以是不是可以考虑作这样一组图：只保留通过$\Upsilon$触发条件的事例，检查他们的不变质量谱？

> 看看保留了哪些Trigger，尝试一下高pT Upsilon trigger
>
> 看看不加顶点限制的Upsilon （1S, 2S, 3S）

## 25 Feb. 2025

### Upsilon spectrum.

Actually, even with all triggers and a limited amount of data (~ 32k Event), Upsilon proved clearly visible.

<img src="images/Upsilon_inclusive_32kEvt.png" alt="Upsilon_inclusive_32kEvt" style="zoom:50%;" />

That is without applying cuts, yet the peaks of $\Upsilon(1S),\Upsilon (2S), \Upsilon(3S) $ have become readily visible. We shall say with much confidence that we can find $\Upsilon$ mesons pretty well.

We rule out the "Upsilon smeared by background from Jpsi trigger data" hypothesis.

### Vertexing of Mesons

Vertexing to reconstruct intermidiate particles ($J/\psi, \Upsilon, \phi$) is crucial, yet it might not be the case if we impose strict limits on the vertexing between the intermidiate particles.

In the triple-$J/\psi$ analysis note (CMS AN-20-146), the authors did not apply vertexing restrictions in the "triple-$J/\psi$" fit. Instead, they used the `fromPV()` and `pvAssociationQuality()` attributes of the final-state muons. This restriction alone is able to reduce the effect of pileup greatly in Run 2.

#### New Idea: Using `fromPV()` and `pvAssociationQuality()` Attributes of the Final-state Particles

In producing the final-state particles, we weaken the vertexing restrictions, and instead use the `fromPV()` and `pvAssociationQuality()` attributes of the final-state particles to filter out the pileup.

For $J/\psi + J/\psi + \Upsilon$ analysis, we require the following for vertexing in producing ntuples.

* vertexing for $J/\psi \rightarrow \mu^+ + \mu^-$ : require > 1% probability (as is required before)
* vertexing for $\Upsilon \rightarrow \mu^+ + \mu^-$: require > 1% probability (as is required before)
* $\mu^\pm$  `fromPV()`: 2 or 3

For $J/\psi + J/\psi + \phi$ analysis, we require the following for vertexing in producing ntuples.

* vertexing for $J/\psi \rightarrow \mu^+ + \mu^-$ : require > 1% probability (as is required before)
* vertexing for $\phi \rightarrow K^+ + K^-$: require > 1% probability (as is required before)
* vertexing for $J/\psi + J/\psi$: require a valid fit.
* $\mu^\pm$ & $K^\pm$  `fromPV()` : 2 or 3

For $J/\psi + \Upsilon + \phi$ analysis, we require the following for vertexing in producing ntuples.

* vertexing for $J/\psi \rightarrow \mu^+ + \mu^-$ : require > 1% probability (as is required before)
* vertexing for $\Upsilon \rightarrow \mu^+ + \mu^-$: require > 1% probability (as is required before)
* vertexing for $\phi \rightarrow K^+ + K^-$: require > 1% probability (as is required before)
* $\mu^\pm$ & $K^\pm$  `fromPV()` : 2 or 3

While making such changes, it is still important to keep a record of the "triple-meson" vertex fitting. We may still need it for future filtering.

#### Possible Implementation with CMSSW code in `TPS-Onia2MuMu`

##### Extracting `fromPV()` and `pvAssociationQuality()` attributes of the muons

The `pat::Muon` does not have `fromPV()` and `pvAssociationQuality()` attributes by itself. However, given that the `pat::Muon` is associated with a `pat::PackedCandidate` as a track, we can use the `pat::PackedCandidate` to extract these attributes.

Luckily, there is already a loop designed to loop over the `pat::PackedCandidate` to remove the muon tracks from the list of all tracks. We can add the extraction of `fromPV()` and `pvAssociationQuality()` attributes in this loop.

```cpp
for (edm::View<pat::Muon>::const_iterator iMuonP  = thePATMuonHandle->begin();
		                                  iMuonP != thePATMuonHandle->end();
                                        ++iMuonP)
	{
        try{
		     /*****************************
		    * Some muon properties here.
		    *****************************/
		    for (std::vector<edm::View<pat::PackedCandidate>::const_iterator>::const_iterator iTrackfID  = nonMuonPionTrack.begin();
		                                                                                      iTrackfID != nonMuonPionTrack.end(); 
                                                                                            ++iTrackfID                             )
		    {
                try{
		    	    if(iMuonP->track().isNull()){
		    	    	continue;
		    	    }
		    	    edm::View<pat::PackedCandidate>::const_iterator iTrackf = *(iTrackfID);
		    	    iMuonP->track()->px();
                    // Match using the momentum. [Annotated by Eric Wang, 20240704]                  
		    	    if (   iTrackf->px() == iMuonP->track()->px() 
                        && iTrackf->py() == iMuonP->track()->py() 
                        && iTrackf->pz() == iMuonP->track()->pz()) {
                        // [New Code] Here we can extract the fromPV() and pvAssociationQuality() attributes of the muon.
                        muFromPV->push_back(iTrackf->fromPV());
                        muPVAssociationQuality->push_back(iTrackf->pvAssociationQuality());
                        // [End of New Code]
		    	    	nonMuonPionTrack.erase(iTrackfID);
		    	    	iTrackfID = iTrackfID - 1;
		    	    }
                } catch(...){
                    continue;
                }
		    }
		    /*****************************
		    * Some Trigger matching here
		    *****************************/
            } catch(...){
                continue;
            }
	}
```

##### Extracting `fromPV()` and `pvAssociationQuality()` attributes of the $K^{\pm}$ tracks

For the $K^{\pm}$ tracks, we can do the extraction directly from the `pat::PackedCandidate` object, yet we can only save this for the $K^{\pm}$ tracks that are picked as candidates for the $\phi$ meson.

In storing the $K^{\pm}$ tracks, we can add the extraction of `fromPV()` and `pvAssociationQuality()` attributes.

```cpp
// Kaon 1
Phi_K_1_px->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->px());
Phi_K_1_py->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->py());
Phi_K_1_pz->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->pz());
Phi_K_1_pt->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->pt());
Phi_K_1_eta->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->eta());
Phi_K_1_phi->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->phi());
// [New Code] extracting fromPV() and pvAssociationQuality() attributes
Phi_K_1_fromPV->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->fromPV());
Phi_K_1_pvAssociationQuality->push_back(nonMuonPionTrack[KPair_Phi->second[0]]->pvAssociationQuality());
// [End of New Code]
```

##### Supplimentary: Storing the `fromPV()` and `pvAssociationQuality()` attributes in the TTree

Apparently, these new atrributes require new branches in the TTrees. We can add these branches in the `TPS-Onia2MuMu` analyzer.

In `src/MultiLepPAT.h`, when declaring the `MultiLepPAT` class:

```cpp
//...
vector<int>         *muIsPatLooseMuon, *muIsPatTightMuon, *muIsPatSoftMuon, *muIsPatMediumMuon;
// [New Code] Adding the new branches for fromPV() and pvAssociationQuality() of muons.
vector<int>         *muFromPV, *muPVAssociationQuality;
// [End of New Code]
//...
```

For the $K^{\pm}$ tracks, we can add the branches in the corresponding place in the declaration of `MultiLepPAT`:
```cpp
//...
vector<float>       *Phi_K_2_eta, *Phi_K_2_phi, *Phi_K_2_pt;
// [New Code] Adding the new branches for fromPV() and pvAssociationQuality() of K^{\pm} tracks.
vector<int>         *Phi_K_1_fromPV, *Phi_K_1_pvAssociationQuality;
vector<int>         *Phi_K_2_fromPV, *Phi_K_2_pvAssociationQuality;
// [End of New Code]
//...
```

In `src/MultiLepPAT.cc`, when constructing `MultiLepPAT`:

> Reminder 1: despite being `enum` types in the `pat::PackedCandidate`, `fromPV()` and `pvAssociationQuality()` are stored as `int` in the `pat::PackedCandidate`. 
>
> Reminder 2: when initializing the branches in the constructor, the order of the branches should be consistent with the order of the variables in the class declaration.

```cpp
//... 
muIsPatLooseMuon(0), muIsPatTightMuon(0), muIsPatSoftMuon(0), muIsPatMediumMuon(0),
// [New Code] Adding the new branches for fromPV() and pvAssociationQuality() of muons.
muFromPV(0), muPVAssociationQuality(0),
// [End of New Code]
```

For the $K^{\pm}$ tracks, we can add the branches in the corresponding place in the constructor of `MultiLepPAT`:

```cpp
//...
Phi_K_2_eta(0), Phi_K_2_phi(0), Phi_K_2_pt(0),
// [New Code] Adding the new branches for fromPV() and pvAssociationQuality() of K^{\pm} tracks.
Phi_K_1_fromPV(0), Phi_K_1_pvAssociationQuality(0),
Phi_K_2_fromPV(0), Phi_K_2_pvAssociationQuality(0),
//...
```

In `src/MultiLepPAT.cc`, after filling the branches into the TTree:

```cpp
//...
muIsPatMediumMuon->clear();
// [New Code] Filling the new branches for fromPV() and pvAssociationQuality() of muons.
muFromPV->clear();
muPVAssociationQuality->clear();
// [End of New Code]
//...
```

For the $K^{\pm}$ tracks, we have to clear also:

```cpp
//...
Phi_K_2_eta->clear();
// [New Code] Filling the new branches for fromPV() and pvAssociationQuality() of K^{\pm} tracks.
Phi_K_1_fromPV->clear();
Phi_K_1_pvAssociationQuality->clear();
Phi_K_2_fromPV->clear();
Phi_K_2_pvAssociationQuality->clear();
//...
```

In `MultiLepPAT::beginJob()`, we have to initialize the new branches:

```cpp
//...
X_One_Tree->Branch("muIsPatMediumMuon", &muIsPatMediumMuon);
// [New Code] Adding the new branches for fromPV() and pvAssociationQuality() of muons.
X_One_Tree->Branch("muFromPV", &muFromPV);
X_One_Tree->Branch("muPVAssociationQuality", &muPVAssociationQuality);
// [End of New Code]
//...
```

For the $K^{\pm}$ tracks, we have to initialize the new branches:

```cpp
//...
X_One_Tree->Branch("Phi_K_2_eta", &Phi_K_2_eta);
// [New Code] Adding the new branches for fromPV() and pvAssociationQuality() of K^{\pm} tracks.
X_One_Tree->Branch("Phi_K_1_fromPV", &Phi_K_1_fromPV);
X_One_Tree->Branch("Phi_K_1_pvAssociationQuality", &Phi_K_1_pvAssociationQuality);
X_One_Tree->Branch("Phi_K_2_fromPV", &Phi_K_2_fromPV);
X_One_Tree->Branch("Phi_K_2_pvAssociationQuality", &Phi_K_2_pvAssociationQuality);
//...
```

