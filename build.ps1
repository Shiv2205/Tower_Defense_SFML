param(
  [string] $type="build",
  [string] $build="reg"
)

if ($type -eq "dev")
{
  ./build.ps1
  ./build.ps1 -type run
}
elseif ($type -eq "build")
{
  if ($build -eq "full") { cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -S . -B .\build }
  cmake --build .\build
}
elseif ($type -eq "run")
{
  ./build/bin/Debug/sfml_game.exe
}
elseif ($type -eq "clean")
{
  Remove-Item ./build -Recurse -Force
}