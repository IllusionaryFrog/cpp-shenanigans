{ pkgs, lib, config, inputs, ... }:

{
  # See full reference at https://devenv.sh/reference/options/

  packages = [
    pkgs.gcc
    pkgs.cmake
    pkgs.ninja
    pkgs.clang-tools
  ];
}
