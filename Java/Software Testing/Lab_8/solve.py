import angr
import claripy

symArgSize = 50
symArg = claripy.BVS("sym_arg", 8 * symArgSize)

proj = angr.Project("./target")
argv = [proj.filename]
argv.append(symArg)
state = proj.factory.entry_state(args=argv)

simgr = proj.factory.simulation_manager(state)
find_addr = 0x401060
avoid_addr = []
simgr.explore(find=find_addr, avoid=avoid_addr)

found = simgr.found[0]
print(found.solver.eval(symArg, cast_to=bytes))

