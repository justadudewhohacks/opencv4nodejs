import * as path from 'path'

export function resolvePath(filePath?: string, file?: string): string {
  if (!filePath) {
    return ''
  }
  return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/')
}

/**
  * detect if electron https://github.com/electron/electron/issues/2288
 */
export function isElectronWebpack() {
  // return process.versions.hasOwnProperty('electron');
   // assume module required by webpack if no system path inv envs
   return !process.env.path
   // eslint-disable-next-line @typescript-eslint/no-explicit-any
   && global.window && global.window.process && (global.window.process as any).type
   && global.navigator && ((global.navigator.userAgent || '').toLowerCase().indexOf(' electron/') > -1)
}
