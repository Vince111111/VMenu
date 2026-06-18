#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "game.h"

void dVentilationSystem_Update(VentilationSystem_Operation__Enum op, int32_t ventId, MethodInfo* method) {
	if (State.ShowHookLogs) LOG_DEBUG("Hook dVentilationSystem_Update executed");
	
	// If BlockVenting is enabled and operation is Enter or Move, kick them out immediately
	if (!State.PanicMode && State.BlockVenting && (op == VentilationSystem_Operation__Enum::Enter || op == VentilationSystem_Operation__Enum::Move)) {
		LOG_INFO(std::format("Block Venting: Kicked player from vent {}", ventId).c_str());
		// Call StartCleaning to kick them out
		VentilationSystem_Update(VentilationSystem_Operation__Enum::StartCleaning, ventId, NULL);
		return; // Don't process the original Enter/Move operation
	}
	
	VentilationSystem_Update(op, ventId, method);
}
