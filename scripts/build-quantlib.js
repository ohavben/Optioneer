'use strict';

// Do this as the first thing so that any code reading it knows the right env.
process.env.BABEL_ENV = 'development';
process.env.NODE_ENV = 'development';
process.env.QUANTLIB_ENV = '1.22';

// Makes the script crash on unhandled rejections instead of silently
// ignoring them. In the future, promise rejections that are not handled will
// terminate the Node.js process with a non-zero exit code.
process.on('unhandledRejection', err => {
  throw err;
});

// Ensure environment variables are read.
require('../config/env');
const fs = require('fs');
//const chalk = require('react-dev-utils/chalk');
//const webpack = require('webpack');
//const WebpackDevServer = require('webpack-dev-server');
const clearConsole = require('react-dev-utils/clearConsole');
//const checkRequiredFiles = require('react-dev-utils/checkRequiredFiles');
//const {
//  choosePort,
//  createCompiler,
//  prepareProxy,
//  prepareUrls,
//} = require('react-dev-utils/WebpackDevServerUtils');
//const openBrowser = require('react-dev-utils/openBrowser');
const semver = require('semver');
const paths = require('../config/paths');
//const configFactory = require('../config/webpack.config');
//const createDevServerConfig = require('../config/webpackDevServer.config');
//const getClientEnvironment = require('../config/env');
//const react = require(require.resolve('react', { paths: [paths.appPath] }));

const getClientEnvironment = require('../config/env');
const env = getClientEnvironment(paths.publicUrlOrPath.slice(0, -1));

const dockerCLI = require('docker-cli-js');
//const DockerOptions = dockerCLI.Options;
const Docker = dockerCLI.Docker;
const { dockerCommand } = require('docker-cli-js');

// default options
const options = {
    machineName: 'undefined', // uses local docker
    currentWorkingDirectory: '../config/emscripten', // uses current working directory
    echo: true, // echo command output to stdout/stderr
    env: process.env.QUANTLIB_ENV,
    stdin: undefined,
};

const docker = new Docker(options);

async function runner(){
    try {
        await docker.command('build -t emscripten-quantlib ../config/emscripten');
        await docker.command('docker run -v ${pwd}/public:/dist --rm emscripten-quantlib cp -r quantlib.js quantlib.wasm ./dist')
    } catch(error){
        throw error
    } 
}

runner();