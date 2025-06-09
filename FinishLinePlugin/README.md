# rFactor 2 Finish Line Plugin

This plugin for rFactor 2 automatically takes your car off track when you cross the finish line during a race. It uses the rF2 Shared Memory Map Plugin to detect finish line crossings and control the car.

## Requirements

- rFactor 2
- rF2 Shared Memory Map Plugin (included in repository)
- Visual Studio 2013 or later (for building)

## Installation

1. Build the plugin using Visual Studio
2. Copy the compiled `FinishLinePlugin.dll` to your rFactor 2 `Plugins` directory
3. Make sure the rF2 Shared Memory Map Plugin is installed and running

## Usage

1. Start rFactor 2
2. The plugin will automatically activate when you enter a race
3. When you cross the finish line, the plugin will:
   - Detect the finish line crossing
   - Turn the steering wheel to full lock
   - Apply full brakes
   - Remove throttle input

## Building from Source

1. Open the solution in Visual Studio
2. Build the solution in Release mode
3. The compiled DLL will be in the `Release` directory

## Notes

- The plugin only activates during races
- It will only take the car off track once per race (when crossing the finish line)
- The plugin can be disabled by removing it from the Plugins directory

## License

This plugin is released under the GPL-3.0 license, same as the rF2 Shared Memory Map Plugin.
