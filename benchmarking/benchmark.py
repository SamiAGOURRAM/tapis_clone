import json
import math
import os
import sys
import time
from easyprocess import EasyProcess

from info import *
from options import *

assert (len(sys.argv) >= 3)
result_path = sys.argv[1]
command = sys.argv[2]

assert (command in ["run", "run_tool", "run_all", "results"])


def get_command(tool, name):
    benchmark = get_benchmark_info(name)
    assert (benchmark is not None)
    if tool == "tapis":
        command = TAPIS_PATH
        command += " --ice.learner.index_domains " + benchmark["parameters"]["tapis"]["index_domain"]
        command += " --ice.learner.data_domains " + benchmark["parameters"]["tapis"]["data_domain"]
        command += " --absint-domain " + benchmark["parameters"]["tapis"]["absint_domain"]
        command += " --qdt.quantifiers " + str(benchmark["parameters"]["tapis"]["quantifiers"])
        if "attr_from_spec" in benchmark["parameters"]["tapis"] and benchmark["parameters"]["tapis"][
            "attr_from_spec"] == False:
            command += " --no-ice.learner.attr_from_spec "
        if "attr_from_program" in benchmark["parameters"]["tapis"] and benchmark["parameters"]["tapis"][
            "attr_from_program"] == False:
            command += " --no-ice.learner.attr_from_program "
        if "mix_data_indexes" in benchmark["parameters"]["tapis"] and benchmark["parameters"]["tapis"][
            "mix_data_indexes"] == True:
            command += " --ice.learner.mix_data_indexes "
        if "abstract_summary_input_arrays" in benchmark["parameters"]["tapis"] and benchmark["parameters"]["tapis"][
            "abstract_summary_input_arrays"] == True:
            command += " --no-qdt.abstract-summary-input-arrays "
        command += " " + os.path.join(TAPIS_BENCHMARK_PATH, benchmark["relative_path"])
        return command
    elif tool == "spacer":
        return Z3_PATH + " fp.spacer.q3.use_qgen=true fp.spacer.ground_pobs=false fp.spacer.mbqi=false fp.spacer.use_euf_gen=true " + os.path.join(
            CHC_BENCHMARK_PATH, benchmark["relative_path"].replace(".c", ".smt2"))
    elif tool == "freqhorn":
        return FREQHORN_PATH + " " + os.path.join(CHC_BENCHMARK_PATH, benchmark["relative_path"].replace(".c", ".smt2"))
    elif tool == "ultimate-automizer":
        return UA_PATH + " --spec " + SV_UNREACH_CALL_PRP_PATH + " --architecture 32bit simple --file " + os.path.join(
            UA_BENCHMARK_PATH, benchmark["relative_path"])
    elif tool == "prophic3":
        return PROPHIC_PATH + " " + os.path.join(VMT_BENCHMARK_PATH, benchmark["relative_path"]).replace(".c", ".vmt")
    elif tool == "diffy":
        return DIFFY_PATH + " " + os.path.join(DIFFY_BENCHMARK_PATH, benchmark["relative_path"])
    elif tool == "vajra":
        return VAJRA_PATH + " " + os.path.join(DIFFY_BENCHMARK_PATH, benchmark["relative_path"])
    elif tool == "rapid":
        return "python3 " + BENCHMARKING_FOLDER + "/helpers/rapid.py " + os.path.join(RAPID_BENCHMARK_PATH, benchmark[
            "relative_path"]).replace(".c", ".spec")


def get_result(tool, benchmark):
    bench_res_path = os.path.join(os.path.join(result_path, tool), benchmark + ".json")
    info = get_benchmark_info(benchmark)
    if tool not in info["supported_by"]:
        return False
    if tool == "spacer":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and ("sat" == tr[1] or "unsat" == tr[1]):
                        if "unsat" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                        break
                    elif tr[0] < time and (not is_safe) and ("unknown" in tr[1]):
                        time = math.inf
                        failed = False
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "freqhorn":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and ("define-fun" in tr[1] or "unsat" in tr[1]):
                        if "unsat" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                    elif tr[0] < time and (not is_safe) and ("unknown" in tr[1]):
                        time = math.inf
                        failed = False
                        break
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "tapis":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] < 0.05:
                        pass
                    elif tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and ("SAFE" in tr[1] or "UNSAFE" in tr[1]):
                        if "UNSAFE" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                        break
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "prophic3":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] < 0.05:
                        pass
                    elif tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and ("sat" in tr[1] or "unsat" in tr[1]):
                        if "unsat" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                        break
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "ultimate-automizer":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and (tr[1].endswith("TRUE") or tr[1].endswith("FALSE")):
                        if tr[1].endswith("FALSE"):
                            is_safe = False
                        time = tr[0]
                        failed = False
                        break
                    else:
                        time = math.inf
                        failed = False
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "diffy":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and (
                            "DIFFY_VERIFICATION_SUCCESSFUL" in tr[1] or "DIFFY_VERIFICATION_FAILED" in tr[1]):
                        if "DIFFY_VERIFICATION_FAILED" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                        break
                    elif tr[0] < time and (not is_safe) and ("DIFFY_VERIFICATION_UNKNOWN" in tr[1]):
                        time = math.inf
                        failed = False
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "vajra":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and (
                            "VAJRA_VERIFICATION_SUCCESSFUL" in tr[1] or "VAJRA_VERIFICATION_FAILED" in tr[1]):
                        if "VAJRA_VERIFICATION_FAILED" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                        break
                    elif tr[0] < time and (not is_safe) and ("VAJRA_VERIFICATION_UNKNOWN" in tr[1]):
                        time = math.inf
                        failed = False
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "lambda":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and ("safe" in tr[1] or "VAJRA_VERIFICATION_FAILED" in tr[1]):
                        if "VAJRA_VERIFICATION_FAILED" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                    elif tr[0] < time and ("VAJRA_VERIFICATION_UNKNOWN" in tr[1]):
                        time = math.inf
                        failed = False
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    elif tool == "rapid":
        if os.path.isfile(bench_res_path):
            with open(bench_res_path, 'r') as f:
                data = json.load(f)
                time = math.inf
                failed = True
                is_safe = True
                for tr in data["times"]:
                    if tr[0] < 0.05:
                        pass
                    elif tr[0] > timeout:
                        failed = False
                    elif tr[0] < time and ("SAFE" in tr[1] or "UNSAFE" in tr[1]):
                        if "UNSAFE" in tr[1]:
                            is_safe = False
                        time = tr[0]
                        failed = False
                    elif tr[0] < time and (not is_safe) and ("UNKNOWN" in tr[1]):
                        time = math.inf
                        failed = False
                if failed:
                    return False
                else:
                    if time is math.inf:
                        return False
                    else:
                        if is_safe:
                            return True
                        else:
                            return True
    else:
        return False


def run_one(tool, program):
    b_timeout = timeout + 1
    command = get_command(tool, program)
    result = {
        "name": program,
        "tool": tool,
        "times": []
    }
    for i in range(tries):
        print("    %s - %s - try %d" % (tool, program, i + 1))
        print(("timeout %ds " % b_timeout) + command)
        start_time = time.time()
        proc = EasyProcess(("timeout %ds " % b_timeout) + command).call()
        end_time = time.time()
        output = proc.stdout
        elapsed_time = round(end_time - start_time, 2)
        if round(elapsed_time + 1) < b_timeout:
            b_timeout = round(elapsed_time + 1)
        result["times"].append((elapsed_time, output))

    if not os.path.exists(result_path):
        os.makedirs(result_path)
    if not os.path.exists(os.path.join(result_path, tool)):
        os.makedirs(os.path.join(result_path, tool))

    bench_res_path = os.path.join(os.path.join(result_path, tool), program + ".json")
    with open(bench_res_path, "w") as file:
        json.dump(result, file)


def run_tool(tool):
    print("  # Running all benchmarks for tool: " + tool)
    for benchmark in benchmarks:
        if tool not in benchmark["supported_by"]:
            continue
        run_one(tool, benchmark["name"])


def run_all():
    for tool in tools:
        run_tool(tool)


def get_results(tool):
    res = {}
    for benchmark in benchmarks:
        if benchmark["source"] not in res:
            res[benchmark["source"]] = {}
        if benchmark["source"] == "sv-comp":
            if benchmark["expected_verdict"] not in res[benchmark["source"]]:
                res[benchmark["source"]][benchmark["expected_verdict"]] = 0
        else:
            if "iterative" not in res[benchmark["source"]]:
                res[benchmark["source"]]["iterative"] = 0
            if "rec" not in res[benchmark["source"]]:
                res[benchmark["source"]]["rec"] = 0
            if "mut-rec" not in res[benchmark["source"]]:
                res[benchmark["source"]]["mut-rec"] = 0
        if tool not in benchmark["supported_by"]:
            continue
        if get_result(tool, benchmark["name"]):
            if benchmark["source"] == "sv-comp":
                res[benchmark["source"]][benchmark["expected_verdict"]] += 1
            else:
                if "iterative" in benchmark["relative_path"]:
                    res[benchmark["source"]]["iterative"] += 1
                elif "mut-rec" in benchmark["relative_path"]:
                    res[benchmark["source"]]["mut-rec"] += 1
                elif "rec" in benchmark["relative_path"]:
                    res[benchmark["source"]]["rec"] += 1
    return res


if command == "run":
    assert (len(sys.argv) >= 5)
    tool = sys.argv[3]
    program = sys.argv[4]

    assert (tool in tools);

    run_one(tool, program)
elif command == "run_tool":
    assert (len(sys.argv) >= 4)
    tool = sys.argv[3]

    assert (tool in tools)

    run_tool(tool)
elif command == "run_all":
    print("# Running all benchmarks")
    run_all()
elif command == "results":
    res_tools = []
    if len(sys.argv) >= 4:
        for i in range(3, len(sys.argv)):
            res_tools.append(sys.argv[i])
    else:
        res_tools = tools

    for tool in res_tools:
        results = get_results(tool)
        print("- " + tool + ": \n"
              "  - SV-COMP: \n"
              "    - safe: " + str(results["sv-comp"]["safe"]) + "/84 \n"
              "    - unsafe: " + str(results["sv-comp"]["unsafe"]) + "/37 \n"
              "  - TAPIS-Bench: \n"
              "    - iterative: " + str(results["tapis-bench"]["iterative"]) + "/49 \n"
              "    - rec: " + str(results["tapis-bench"]["rec"]) + "/37 \n"
              "    - mut: " + str(results["tapis-bench"]["mut-rec"]) + "/8 \n"
              "  - Total: " + str(results["sv-comp"]["safe"] + results["sv-comp"]["unsafe"] + results["tapis-bench"]["iterative"] + results["tapis-bench"]["rec"] + results["tapis-bench"]["mut-rec"]) + "/215  \n"
              "    - safe: \n"
              "      - iterative: " + str(results["sv-comp"]["safe"] + results["tapis-bench"]["iterative"]) + "/133 \n"
              "      - recursive: " + str(results["tapis-bench"]["rec"] + results["tapis-bench"]["mut-rec"]) + "/45 \n"
              "    - unsafe: " + str(results["sv-comp"]["unsafe"]) + "/37")
