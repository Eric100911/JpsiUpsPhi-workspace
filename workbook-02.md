### 8 Apr. 2025

#### $J/\psi+J/\psi+\Upsilon$的更新

![First_J_J_Y_fit](images/J+J+Y_2022_2023_2024_Fit_01.png)

设定如下：

* $J/\psi : p_T > 4 \space \mathrm{GeV/c}, |\eta| < 2.5$

    > * 继续优化
    >
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

> My bad...这个好像是用来处理无信号的假设

yield_SSS甚至没有直接给出值...图中写的是$0\pm0$...

以上的信号都是用的是Gaussian而不是CB，而且$\Upsilon(2S, 3S)$的峰还没有加入，但是预期改善不大。作为报告的话...“声明现阶段不宜看这个反应”？产生截面上限值如何估计？

> $\Upsilon(1S)$原本截面就很低，给出的$\sigma_{\mathrm{eff}}$的下限限制应该会很低，继续做这个过程的意义大吗？

又：正在尝试做triple-$J/\psi$的复现，测试工作进行中。

#### 问题：关于Trigger引起的质量分布bias（？）

查阅CMS HLT info得知，`HLT_Dimuon0_Jpsi3p5_Muon2_v`里面的触发条件中，要求存在一对质量在2.95 GeV至3.25 GeV之间的正反muon对；`HLT_DoubleMu4_3_LowMass_v`的不变质量限制则更宽一些，为0.2 GeV 至8.5 GeV。如果选择质量窗为$[2.0, 4.0]$，我们将有机会看到$[2.95,3.25]$区间出现“本底抬高”吗？

> 虽然说之前看到单独使用`HLT_Dimuon0_Jpsi3p5_Muon2_v`的时候旁边的本底也不那么高？

#### 问题：关于使用HELAC-Onia

1. 如何产生含有$\phi(1020)$样本的事例？（联系邵老师？）

2. 产生的TPS样本里面，$J/\psi$和$\Upsilon(1S)$单独的动力学分布已经和单独产生的分布不太一致。如何理解？是不是和选择的部分子分布函数有关系，还是说“存在另外两个粒子”就是一种条件关联？

    ![compareMix_Jpsi_pT_with_Error](images/compareMix_Jpsi_pT_with_Error.png)

    ![compareMix_Y_pT_with_Error](images/compareMix_Y_pT_with_Error.png)

    > 稍等，这个discrepancy重要吗？

3. 更换随机种子却得到相同的结果，这是为什么？

    > 这应该完全是软件问题...应该直接问开发者？

> 1,3汇总一个“问题情况说明”。

> LDME直接使用默认值即可。

### 15 May. 2025

#### Goal:

$J/\psi+J/\psi+\Upsilon(1S)$ pLHE to MINIAOD workflow.

#### Dataset Name:

In general, we would adopt the name **`JpsiJpsiY1S_TPS_to_6Mu_13p6TeV_HELAC_Onia2_TuneCP5_pythia8`**

We shall start with Run2022C settings and make MC datasets with the following names:

| Data tier   | full name                                                    |
| ----------- | ------------------------------------------------------------ |
| GEN-SIM     | `/JpsiJpsiY1S_TPS_to_6Mu_13p6TeV_HELAC_Onia2_TuneCP5_pythia8/Run3Summer22_124X_mcRun3_2022_realistic_v12_MiniAOD_v4/GENSIM` |
| GEN-SIM-RAW | `/JpsiJpsiY1S_TPS_to_6Mu_13p6TeV_HELAC_Onia2_TuneCP5_pythia8/Run3Summer22_124X_mcRun3_2022_realistic_v12_MiniAOD_v4/RAW` |
| AODSIM      | `/JpsiJpsiY1S_TPS_to_6Mu_13p6TeV_HELAC_Onia2_TuneCP5_pythia8/Run3Summer22_124X_mcRun3_2022_realistic_v12_MiniAOD_v4/AOD` |
| MINIAODSIM  | `/JpsiJpsiY1S_TPS_to_6Mu_13p6TeV_HELAC_Onia2_TuneCP5_pythia8/Run3Summer22_124X_mcRun3_2022_realistic_v12_MiniAOD_v4/MINIAOD` |

#### CMSSW Config from `cmsDriver.py`

##### pLHE-GEN-SIM

A framework can be built from this command first [^1][^2][^6]:

```bash
# 2022 in CMSSW_12_4_14_patch3
cmsDriver.py \
Configuration/Generator/python/Hadronizer_TuneCP5_13TeV_MLM_5f_max4j_LHE_pythia8_cff.py \
--mc --no_exec \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_GENSIM.py \
--eventcontent RAWSIM --step GEN,SIM --datatier GEN-SIM \
--conditions 124X_mcRun3_2022_realistic_v12 \
--beamspot Realistic25ns13p6TeVEarly2022Collision \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--filein file:JJY_TPS_test.lhe \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_GENSIM.root

# 2022 post-EE in CMSSW_12_4_14_patch3
cmsDriver.py \
Configuration/Generator/python/Hadronizer_TuneCP5_13TeV_MLM_5f_max4j_LHE_pythia8_cff.py \
--mc --no_exec \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_GENSIM.py \
--eventcontent RAWSIM --step GEN,SIM --datatier GEN-SIM \
--conditions 124X_mcRun3_2022_realistic_postEE_v1 \
--beamspot Realistic25ns13p6TeVEarly2022Collision \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--filein file:JJY_TPS_test.lhe \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_GENSIM.root

# 2023 in CMSSW_13_0_13

# 2023 post-BPix in CMSSW_13_0_13

# 2024

```

The hadronization fragment shall be modified to be like[^12]:

```python
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8aMCatNLOSettings_cfi import *
from Configuration.Generator.PSweightsPythia.PythiaPSweightsSettings_cfi import *
from Configuration.Generator.MCTunesRun3ECM13p6TeV.PythiaCP5Settings_cfi import *

process.generator = cms.EDFilter("Pythia8ConcurrentHadronizerFilter",
    PythiaParameters = cms.PSet(
        pythia8CommonSettingsBlock,       # Common Pythia8 settings  
        pythia8CP5SettingsBlock,          # CMS CP5 tune for Pythia8 
        pythia8aMCatNLOSettingsBlock,     # Settings for aMC@NLO matching  
        pythia8PSweightsSettingsBlock,    # Settings for parton shower (PS) weights  

        processParameters = cms.vstring(
            "TimeShower:nPartonsInBorn = -1",     # Number of partons in Born process (-1 = auto)  
            "TimeShower:mMaxGamma = 4",           # Maximum photon energy in final-state QED shower (GeV)  
            "PDF:pSet = 7",                       # Use PDF set ID 7   
            
            # Decay mode settings
            "23:onMode = 0",                      # Disable all decays of Z boson  
            "23:onIfMatch = 13 -13",              # Allow only Z to mu+mu-
            "443:onMode = 0",                     # Disable all decays of Jpsi 
            "443:onIfMatch = 13 -13",             # Allow only Jpsi to mu+mu- decay
            "20443:onMode = 0",                   # Disable all decays of Chi_c1  
            "20443:onIfAny = 443",                # Allow Chi_c1 to Jpsi decay  
            "445:onMode = 0",                     # Disable all decays of Chi_c2  
            "445:onIfAny = 443",                  # Allow Chi_c2 to Jpsi decay  
            "10441:onMode=0",                     # Disablealldecaysofh_c
            "10441:onIfAny = 443",                # Allow h_c to Jpsi decay  
            "100443:onMode = 0",                  # Disable all decays of psi(2S)  
            "100443:onIfAny = 443",               # Allow psi(2S) to Jpsi decay 
            "553:onMode = 0",                     # Disable all decays of Upsilon(1S)
            "553:onIfMatch = 13 -13",             # Allow Upsilon(1S) to mu+mu- decay
            "100553:onMode = 0",                  # Disable all decays of Upsilon(2S)
            "100553:onIfMatch = 13 -13",          # Allow Upsilon(2S) to mu+mu- decay
            "200553:onMode = 0",                  # Disable all decays of Upsilon(3S)
            "200553:onIfMatch = 13 -13",          # Allow Upsilon(3S) to mu+mu- decay
        ),

        parameterSets = cms.vstring(
            "pythia8CommonSettings",      
            "pythia8CP5Settings",         
            "pythia8aMCatNLOSettings",    
            "processParameters",          
            "pythia8PSweightsSettings"    
        )
    ),
    comEnergy = cms.double(13600),                    # Collision energy, needs to be same as the setting in HELAC-Onia.
    maxEventsToPrint = cms.untracked.int32(0),        # Do not print event details  
    pythiaHepMCVerbosity = cms.untracked.bool(False), # Disable HepMC event output verbosity  
    pythiaPylistVerbosity = cms.untracked.int32(0),   # Disable Pythia event listing output  
    filterEfficiency = cms.untracked.double(1.0),     # Set filter efficiency to 1.0 (all events pass)  
)
```

##### DIGI, L1T, HLT[^1][^2][^4][^6]

```bash
# 2022, CMSSW_12_4_14_patch3
cmsDriver.py \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_RAW.py \
--eventcontent PREMIXRAW --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:2022v12 \
--procModifiers premix_stage2,siPixelQualityRawToDigi --datamix PreMix \
--datatier GEN-SIM-RAW \
--conditions 124X_mcRun3_2022_realistic_v12 \
--beamspot Realistic25ns13p6TeVEarly2022Collision \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--pileup_input filelist:/cvmfs/cms.cern.ch/offcomp-prod/premixPUlist/PREMIX-Run3Summer22DRPremix.txt \
--mc --no_exec \
--filein file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_GENSIM.root \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_RAW.root


# 2022 post-EE, CMSSW_12_4_14_patch3
cmsDriver.py \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_RAW.py \
--eventcontent PREMIXRAW --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:2022v14 \
--procModifiers premix_stage2,siPixelQualityRawToDigi --datamix PreMix \
--datatier GEN-SIM-RAW \
--conditions 124X_mcRun3_2022_realistic_postEE_v1 \
--beamspot  Realistic25ns13p6TeVEarly2022Collision \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--pileup_input filelist:/cvmfs/cms.cern.ch/offcomp-prod/premixPUlist/PREMIX-Run3Summer22EEDRPremix.txt \
--mc --no_exec \
--filein file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_GENSIM.root \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_RAW.root

```

> Very careful with the CMSSW release here! Later releases have removed the `HLT:2022v12` settings at `cmsDriver.py`-level.

Here we are using the pileup files obtained via `cvmfs`. A more flexible way to do it is using this script to obtain the pileup files available sites:

```bash
wget https://raw.githubusercontent.com/FNALLPC/lpc-scripts/refs/heads/master/get_files_on_disk.py
python3 get_files_on_disk.py -a T2_CH_CERN T1_US_FNAL_Disk -o PREMIX.txt DATASET_NAME

```

The favored datasets are

| Era                    | Dataset                                                      |
| ---------------------- | ------------------------------------------------------------ |
| Run2022                | `/Neutrino_E-10_gun/Run3Summer21PrePremix-Summer22_124X_mcRun3_2022_realistic_v11-v2/PREMIX` |
| Run2023C               | `/Neutrino_E-10_gun/Run3Summer21PrePremix-Summer23_130X_mcRun3_2023_realistic_v13-v1/PREMIX` |
| Run2023D ("post-BPix") | `/Neutrino_E-10_gun/Run3Summer21PrePremix-Summer23BPix_130X_mcRun3_2023_realistic_postBPix_v1-v1/PREMIX` |
| Run2024                | `/Neutrino_E-10_gun/RunIIISummer24PrePremix-Premixlib2024_140X_mcRun3_2024_realistic_v26-v1/PREMIX` |
| Run2025 (?)            | (No PREMIX dataset so far.)                                  |

> The datasets above are actually inferred from the lists in `cvmfs`.



##### RECO[^1][^2][^6][^12]

```bash
# 2022
cmsDriver.py \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_RECO.py \
--eventcontent AODSIM --step RAW2DIGI,L1Reco,RECO,RECOSIM \
--procModifiers siPixelQualityRawToDigi --datatier GEN-SIM-RAW \
--conditions 124X_mcRun3_2022_realistic_v12 \
--beamspot Realistic25ns13p6TeVEarly2022Collision \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--mc --no_exec \
--filein file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_RAW.root \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_AOD.root

# 2022 post-EE
cmsDriver.py \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_RECO.py \
--eventcontent AODSIM --step RAW2DIGI,L1Reco,RECO,RECOSIM \
--procModifiers siPixelQualityRawToDigi --datatier GEN-SIM-RAW \
--conditions 124X_mcRun3_2022_realistic_postEE_v1 \
--beamspot Realistic25ns13p6TeVEarly2022Collision \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--mc --no_exec \
--filein file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_RAW.root \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22EE_AOD.root
```

##### MINIAOD[^1][^2][^4][^6][^12]

```bash
# 2022, CMSSW_13_0_13
cmsDriver.py \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_SKIM.py \
--eventcontent MINIAODSIM --step PAT \
--datatier MINIAODSIM \
--conditions 124X_mcRun3_2022_realistic_v12 \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--mc --no_exec \
--filein file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_AOD.root \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_MiniAOD.root

# 2022 post-EE, CMSSW_13_0_13
cmsDriver.py \
--python_filename JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_RECO.py \
--eventcontent MINIAODSIM --step PAT \
--datatier MINIAODSIM \
--conditions 124X_mcRun3_2022_realistic_v12 \
--era Run3 --geometry DB:Extended -n -1 \
--customise Configuration/DataProcessing/Utils.addMonitoring \
--nThreads 8 --nStreams 8 \
--mc --no_exec \
--filein file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_AOD.root \
--fileout file:JJY1S_TPS_6Mu_13p6TeV_TuneCP5_pythia8_Run3Summer22_MiniAOD.root
```



#### `CRAB` Config for Running Generation Steps Above

On `CRAB`, running CMSSW config with pLHE input could mean a bit more trouble, especially when we have A LOT of pLHE to process and we are adding PU into consideration.

The first issue is that pLHE could become too large to be transferred to the `CRAB` input sandbox for later processing. In our case, it was \~ 900k events split into \~ 9k files with a total size of \~ 1.8GB, far exceeding the 100MB limit of `CRAB`[^9]. This demands that we do not include pLHE files as inputs in CRAB config, but rather, handle the pLHE file at where they are directly accessible.

For the `GEN-SIM ` step, we are setting the input file source with the PFN to our CERNBox, adding all files into the list of files to be processed, and leaving the job splitting to CRAB. The produced data files will be mostly kept at `T2_CN_Beijing` .

> Very careful here! There have been reports on faulty handling of LHE event ranges.[^15] This was only recently fixed and a section in crab config seems to be required for the thing to work:
> ```python
> config.section_("General")
> config.General.instance = 'preprod'
> ```
>
> 

For the `GEN-SIM ` and `DIGI-L1T-HLT` steps, we prefer conducting them only at `T2_CH_CERN`. For the former one, since the LHE files are at `T3_CH_CERNBOX`, running the tasks at `T2_CH_CERN` seems the safest way to do it. For the latter one, it is because `T2_CH_CERN` has an abundant supply of `PREMIX` files 







#### References:

[^1]:  `cmsDriver.py` hands-on guide from the 17th (?) CMS Induction Event (Feb. 2025, @ CERN), by Phat Srimanobhas (for `cmsDriver.py` general config and `PreMix` configuration.): https://phat-srimanobhas.gitbook.io/cmsinductionwinter2025-cmssw/cmssw-101/cmsdriver

[^2]: PdmV suggestions (esp. `cmsDriver.py` command reference for MC in `Run3Summer2022`, `Run3Summer2022EE`, `Run3Summer23`, `Run3Summer23BPix`) : https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVRun3Analysis

[^3]: A more comprehensive guide: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideSimulation

[^4]: On event mixing for PU simulation: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMixingModule

[^5]: Vertex smearing configurations (for `--beamspot` configurations)(only intended as a list of "what is available", please refer to PdmV suggestions): https://cmssdt.cern.ch/lxr/source/Configuration/StandardSequences/python/VtxSmeared.py 

[^6]: Full chain MC hands-on guide from the 2nd China CMS Winter School (Jan. 2024, @ SYSU), by Zhen Hu and Tongguang Cheng: https://indico.ihep.ac.cn/event/21064/contributions/148451/attachments/75611/93299/FullMC_HandsOn.pdf

[^7]: LXR reference for all sorts of existing `Pythia8ConcurrentHadronizerFilter` fragments: https://cmssdt.cern.ch/lxr/source/Configuration/Generator/python/

[^8]: General crab job reference: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCrab

[^9]: To run crab jobs with LHE input: https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3AdvancedTopic#Running_MC_generation_on_LHE_fil 

[^10]: Another tutorial on running crab jobs with LHE input: https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3AdvancedTutorial#Exercise_5_LHE)

[^11]: PdmV suggestions on MC tuning and PDFs: https://cms-pdmv.gitbook.io/project/mccontact/info-for-mc-production-for-run3-campaigns
[^12]: HELAC-Onia 2.7.6 production and further simulation tutorial, from private communication with Yiyang Zhao.
[^13]: A CMS Talk post which might be useful for configuring "sequential MC production". https://cms-talk.web.cern.ch/t/crab-not-accepting-input-dataset-from-fnal-lpc-storage-site/18135
[^14]: Notes on using `root://` PFN paths in CMSSW config for input files. https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookXrootdService
[^15]: Notes on splitting pLHE inputs with CRAB jobs: https://cms-talk.web.cern.ch/t/every-crab-job-runs-with-the-same-input-event/2489/9
