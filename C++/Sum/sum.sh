#!/bin/bash
#SBATCH --job-name=SUM_CPP
#SBATCH --output=SUM_CPP_%j.log
#SBATCH --partition=compute
#SBATCH --mem=1gb
#SBATCH --nodes=5
#SBATCH --time=00:02:00

. /etc/profile.d/modules.sh

module load openmpi/2.1.2

/opt/openmpi-2.1.2/bin/mpirun ./sum
