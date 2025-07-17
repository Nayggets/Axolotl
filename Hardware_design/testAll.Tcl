# Ouvrir le projet
open_project Axolotl.xpr

# Passer en mode simulation
set_property top my_testbench [get_filesets sim_1]

# Exécuter la simulation pour chaque testbench
set testbenches {"And_tb" "Not_tb" "Or_tb" "Sll_tb" "Slr_tb" "Substract_tb" "Xor_tb" "RAM_tb" "Adder_tb"}

# Dossier de sortie pour les fichiers WDB
set output_dir "./testBenchResult"

file mkdir $output_dir
file mkdir "$output_dir/wafeforms"

set log_file "$output_dir/log_simulation.txt"
set log_id [open $log_file "w"]

proc log_message {msg} {
	global log_id
	puts $log_id $msg
	flush $log_id
}


foreach tb $testbenches {
    log_message "Running testbench: $tb"
    set_property top $tb [get_filesets sim_1]
    launch_simulation
    run 10ns
    set err [catch {run} result]
    if {$err} {
        log_message "Testbench $tb FAILED!"
        log_message $result
    } else {
        log_message "Testbench $tb PASSED!"
        log_message $result
    }
    close_sim
}

# Quitter Vivado
exit
