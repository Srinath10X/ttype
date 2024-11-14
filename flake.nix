{
  description = "TermiType 🚀: A terminal-based typing test application built with C++";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";

  outputs = { self, nixpkgs }:
    let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
    in
    {
      packages.x86_64-linux.default = pkgs.stdenv.mkDerivation {
        pname = "ttype";
        version = "v1.0.0";

        src = ./.;

        buildInputs = [ pkgs.gcc pkgs.gnumake ];
        buildPhase = "make build";
        installPhase = ''mkdir -p $out/bin && cp ttype $out/bin/'';

        cleanPhase = "make clean";
      };

      devShells.x86_64-linux.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gcc
          gnumake
        ];
      };
    };
}
