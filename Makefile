# Purpose of this GNU Make pipeline:
# 1. Drive preCut stage:
#   - For each root file in config/datalist.txt, 
#	  create a job directory in preCut/jobs_$(suffix)/ with the same name.
#   - Copy src/runPreCut.C to each job directory and modify it to read the corresponding root file.
#   - Execute the modified macro in each job directory.
#   - Save the output root file in each job directory.
#   - Merge the output root files into a single root file.
#       - The name of merged file is defined as "preCut-{suffix}.root"
# 2. Drive secCut stage:
#   - Multiple cut conditions will be tested. Our focus will be on Upsilons
#   - The cut condition set is specified in config/cutlist.txt
#       - Sample lines of config/cutlist.txt:
#       	- Ups_pT 4.0 4.5 5.0 5.5 6.0 7.0
# 			- Ups_mu_pT 2.0 2.5 3.0 3.5 4.0 5.0
# 			- Ups_mu_ID loose medium tight
#       - These are translated into job directories in secCut/jobs_$(suffix)/ with the same name.
#       	- For example: Ups_pT_4p0_Ups_mu_pT_2p0_Ups_mu_ID_loose
#   - Copy secCut/secCut.C to each job directory and modify it to apply the corresponding cut condition.
#   - Copy secCut/runSecCut.C to each job directory and modify it to read the corresponding root file.
#   - Execute the modified macro in each job directory.
#   - Plots and data after each cut condition will be saved in the corresponding job directory.
# 3. Drive fitMass stage:
#   - For each job in secCut/jobs_$(suffix)/ ,run runFitMass.C in the job directory.
#   - The output plots will be saved in the corresponding job directory.

# Marker for this job.
suffix=2023_half

rootNtupleDir=/home/storage0/users/chiwang/storage2/CMS-Analysis/JpsiUpsPhi/rootNtuple



# Preparation: generating the job targets.
# preCut stage:
preCut_datalist = $(shell cat config/datalist.txt)
preCut_jobs=$(shell sed -r -e "s|^(.*)\/([^\/]+)\.root$$|\2|g" config/datalist.txt)
preCut_jobdirs=$(addprefix preCut/jobs_$(suffix)/,$(preCut_jobs))
preCut_jobmacros=$(addsuffix /runPreCut.C,$(preCut_jobdirs))
preCut_joboutputs=$(addsuffix /filtered_data_preCut.root,$(preCut_jobdirs))
preCut_output=preCut/preCut_$(suffix).root

# secCut stage:
# - The job list is generated by passing config/cutlist.txt to secCut/makeJobDirs.py
secCut_joblist = $(shell secCut/makeJobs.sh -i config/cutlist.txt)
secCut_jobdirs=$(addprefix secCut/jobs_$(suffix)/,$(secCut_joblist))
secCut_jobmacros=$(addsuffix /runSecCut.C,$(secCut_jobdirs))
secCut_joboutputs=$(addsuffix /filtered_data_secCut.root,$(secCut_jobdirs))

# fitMass stage:
fitMass_jobdirs=$(secCut_jobdirs)
fitMass_jobmacros=$(addsuffix /runFitMass.C,$(fitMass_jobdirs))
fitMass_joboutputs=$(addsuffix /fit_mass.png,$(fitMass_jobdirs))

# Define the target to process the root files
.PHONY: all pre sec fit clean

all: $(preCut_output) $(preCut_joboutputs) $(secCut_joboutputs) $(fitMass_joboutputs)

clean:
	rm -rf preCut/jobs_$(suffix)/* secCut/jobs_$(suffix)/* fitMass/jobs_$(suffix)/*

# preCut stage:
# - General target.

pre: $(preCut_output) $(preCut_joboutputs) preCut/preCut.C

$(preCut_output): $(preCut_joboutputs)
	hadd -f $@ $^

# - Target for one original root file.
preCut/jobs_$(suffix)/%/filtered_data_preCut.root: preCut/jobs_$(suffix)/%/runPreCut.C config/datalist.txt preCut/preCut.C
	cd $(dir $@) && root -x runPreCut.C

# - Target for generating the modified macro.
preCut/jobs_$(suffix)/%/runPreCut.C: preCut/runPreCut.C config/datalist.txt preCut/preCut.C
	mkdir -p $(dir $@)
	sed -e "s|JOB_DATA|$(shell echo $@ | sed -r -e "s|preCut/jobs_$(suffix)\/(.*Run)([0-9]{4,4})(.*)\/runPreCut.C$$|$(rootNtupleDir)/P_Run\2_$(suffix)/\1\2\3.root|g")|g" $< | sed -r -e "s|\/\/\W*#define RUN_JOB|#define RUN_JOB|g" > $@

# secCut stage:
# - General target.
sec: $(secCut_joboutputs)

# - Target for one cut condition.
secCut/jobs_$(suffix)/%/filtered_data_secCut.root: secCut/jobs_$(suffix)/%/runSecCut.C preCut/preCut_$(suffix).root secCut/jobs_$(suffix)/%/secCut.C config/cutlist.txt
	mkdir -p secCut/jobs_$(suffix)/$*
	cd secCut/jobs_$(suffix)/$* && root -x runSecCut.C

# - Target for generating the modified macro.
secCut/jobs_$(suffix)/%/runSecCut.C: secCut/runSecCut.C $(preCut_output)
	mkdir -p secCut/jobs_$$(suffix)/$$*
	cp secCut/runSecCut.C $@

# - Extract the cut info from the cut info text file in job directory.
secCit/jobs_$(suffix)/%/secCut.C: secCut/secCut.C
	mkdir -p secCut/jobs_$$(suffix)/$$*
	


	